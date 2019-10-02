//
//  HashTable.cpp
//  CompressionOppression
//
//  Created by Tran on 5/30/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "HashTable.h"
#include <functional>
//Default length of the sequence
int SEQUENCE_LENGTH = 16;
HashTable::HashTable(int size)
:m_size(size)
{
    for(int i = 0; i < m_size; i++)
    {
        Node* p = new Node;
        p->item = "empty";
        p->next = nullptr;
        table.push_back(p);
    }
}

//Destructor for Hashtable.
HashTable::~HashTable()
{
    //Goes through each bucket in the table.
    for (int i = 0; i < m_size; i++)
    {
        if(table[i] != nullptr)
        {
            Node* m_head = table[i];
            while(m_head != nullptr)
            {
                Node* temp = m_head;
                m_head = m_head->next;
                delete temp;
            }
        }
    }
}

//Returns the corresponding index of a hash value.
int HashTable::hashfunction(string item) const
{
    //int value = key(item);
    unsigned int h = 2166136361u;
    for(int i = 0; i < item.size(); i++)
    {
        h += item.at(i);
        h *= 16777619;
    }
    //Maps the key value onto an index of the vector using the modulo operator.
    return h % m_size;
}

//Adds an item to the hashtable base on its key value.
void HashTable::additem(string item, int offset)
{
    int index = hashfunction(item);
    //If the bucket is empty, initialize it.
    if(table[index]->item == "empty")
    {
        table[index]->item = item;
        table[index]->offset = offset;
    }
    //If bucket is not empty, find the last item.
    else
    {
        Node* head = table[index];
        while(head->next != nullptr)
        {
            head = head->next;
        }
        Node* newitem = new Node;
        newitem->next = nullptr;
        newitem->item = item;
        newitem->offset = offset;
        head->next = newitem;
    }
}

int HashTable::find(const string& item, const string& oldstr, const string& newstr, const int& offset, int& size) const
{
    //Find the key of the
    int index = hashfunction(item);
    if(table[index] != nullptr)
    {
        int maxoffset = -1;
        Node* head = table[index];
        while(head != nullptr)
        {
            if(item == head->item)
            {
                int tempoffset = head->offset;
                int tempsize = SEQUENCE_LENGTH;
                int temp1 = offset + SEQUENCE_LENGTH;
                int temp2 = tempoffset + SEQUENCE_LENGTH;
                //Find how far the sequence extends
                while((temp1 < newstr.size()) && (temp2 < oldstr.size()) && newstr.at(temp1) == oldstr.at(temp2))
                {
                    tempsize++;
                    temp1++;
                    temp2++;
                }
                //Find the best match, because there could be repeat sequences with different offsets
                if(tempsize > size)
                {
                    size = tempsize;
                    maxoffset = tempoffset;
                }
            }
            head = head->next;
        }
        //Return the best offset.
        return maxoffset;
    }
    return -1;
}
