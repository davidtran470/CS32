//
//  Sequence.cpp
//  C32_Project2
//
//  Created by Tran on 4/17/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#include "Sequence.h"

Sequence::Sequence()
: m_size(0)
{
    Dummy = new Node;
    m_head = Dummy;
    m_head->next = m_head;
    m_head->prev = m_head;
}

Sequence::~Sequence ()
{
    //Counter to keep track of the number of items deleted
    Node* curr = m_head->next;
    Node* temp;
    
    //Walk the linked list and delete the items in it.
    while(curr != m_head)
    {
        temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete Dummy;
}

Sequence::Sequence(const Sequence& other)
{
    Dummy = new Node;
    m_head = Dummy;
    m_size = other.m_size;
    m_head->next = m_head;
    m_head->prev = m_head;
    //Walking the linked list of the other Sequence;
    //Temperorary pointers to track each of the old linked list and the new linked list.
    Node* other_curr = other.m_head->next;
    Node* curr = m_head;
    while(other_curr != other.m_head)
    {
        Node* newGuy = new Node;
        newGuy->data = other_curr->data;
        newGuy->prev = curr;
        curr->next = newGuy;
        curr = curr->next;
        other_curr = other_curr->next;
    }
    //Connect the head to the tail
    curr->next = m_head;
    m_head->prev = curr;
}

Sequence& Sequence::operator=(const Sequence& other)
{
    if(this != &other)
    {
        Sequence temp (other);
        swap(temp);
    }
    return *this;
}

bool Sequence::empty() const
{
    //If the next and prev of head are pointing to itself, Sequence is empty.
    if(m_head == m_head->next && m_head == m_head->prev)
        return true;
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    //Returns -1 if the position if out of bounds
    if(!(pos >= 0 && pos <= m_size))
    {
        return -1;
    }
    Node* newGuy = new Node;
    newGuy -> data = value;
    //If list is empty, set the next and prev of the tail to the new Node.
    if(empty())
    {
        newGuy->next = m_head;
        newGuy->prev = m_head;
        m_head->next = newGuy;
        m_head->prev = newGuy;
        m_size++;
        return pos;
    }
    Node* curr = m_head;
    for(int i = 0; curr -> next != m_head && i < pos; i++)
    {
        curr = curr->next;
    }
    //If item is inserted at the head of the list, tail of the list, or the middle of the list.
    newGuy->next = curr->next;
    newGuy->prev = curr;
    curr->next->prev = newGuy;
    curr->next = newGuy;
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    //Keep track of the current postion.
    Node* newGuy = new Node;
    newGuy -> data = value;
    //If list is empty, set the next and prev of the tail to the new Node.
    if(empty())
    {
        newGuy->next = m_head;
        newGuy->prev = m_head;
        m_head->next = newGuy;
        m_head->prev = newGuy;
        m_size++;
        return 0;
    }
    Node* curr;
    int counter = 0;
    for(curr = m_head->next; curr != m_head; curr = curr->next)
    {
        //If the value is inserted in the beginning or middle of the list.
        if(value <= curr->data)
        {
            newGuy->next = curr;
            newGuy->prev = curr->prev;
            curr->prev->next = newGuy;
            curr->prev = newGuy;
            break;
        }
        counter++;
    }
    //If the value should be inserted at the end.
    if(curr == m_head)
    {
        newGuy->next = curr;
        newGuy->prev = curr->prev;
        curr->prev->next = newGuy;
        curr->prev = newGuy;
    }
    m_size++;
    return counter;
}

bool Sequence::erase(int pos)
{
    if (pos < 0  ||  pos >= size())
        return false;
    
    //If there is only one element in the Sequence
    if(m_head->next == m_head->prev)
    {
        delete m_head->next;
        m_head->next = m_head;
        m_head->prev = m_head;
        m_size--;
        return true;
    }
    
    //Walks the linked list to the derised position
    Node* curr = m_head->next;
    for(int i = 0; curr->next != m_head && i < pos; i++)
    {
        curr = curr -> next;
    }
    
    //Erases the Node at the beginning, middle, and end of the list.
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    delete curr;
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int counter = 0;
    while (find(value) != -1)
    {
        erase(find(value));
        counter++;
    }
    return counter++;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0  ||  pos >= size())
        return false;
    //Walking the linked list.
    Node* curr = m_head->next;
    for(int i = 0; curr->next != m_head && i < pos; i++)
    {
        curr = curr -> next;
    }
    //Setting parameter value equal to value in node.
    value = curr->data;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0  ||  pos >= size())
    return false;
    //Walking the linked list.
    Node* curr = m_head->next;
    for(int i = 0; curr->next != m_head && i < pos; i++)
    {
        curr = curr -> next;
    }
    //Setting value in node equal to the parameter value.
    curr->data = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node* curr;
    int counter = 0;
    for (curr = m_head->next; curr != m_head; curr = curr->next)
    {
        //When value is found, return the counter of position.
        if(value == curr->data)
        {
            return counter;
        }
        counter++;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    //Switch the heads of the Sequences to swap their linked lists.
    other.m_head = Dummy;
    m_head = other.Dummy;
    
    //Switch the dummy nodes of the Sequences
    Node* temp = Dummy;
    Dummy = other.Dummy;
    other.Dummy = temp;
    
    //Switch the sizes of the Sequences so that they now correspond with their respective linked lists.
    int tempsize = m_size;
    m_size = other.m_size;
    other.m_size = tempsize;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if(seq2.empty() || seq1.empty() || seq2.size() > seq1.size())
    {
        return -1;
    }
    int i = 0;
    while (i <= seq1.size() - seq2.size())
    {
        int x = 0;
        //Check the elements of seq1 with the elements of seq2
        while (x < seq2.size())
        {
            ItemType temp1;
            ItemType temp2;
            seq1.get(i + x, temp1);
            seq2.get(x, temp2);
            if(temp1 == temp2)
            {
                //If all elements are successfully checked, the subsequence should return the position i.
                if(x == seq2.size() - 1)
                {
                    return i;
                }
                x++;
            }
            else
            {
                break;
            }
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    //To avoid aliasing problem, create temporary Sequence.
    Sequence temp;
    int tempsize = seq1.size();
    if (seq2.size() > seq1.size())
    {
        tempsize = seq2.size();
    }
    int insertpos = 0;
    //Walk each linked list and add elements to temporary linked list accordingly
    for(int i = 0; i < tempsize; i++)
    {
        if(i < seq1.size())
        {
            ItemType temp1;
            seq1.get(i, temp1);
            temp.insert(insertpos, temp1);
            insertpos++;
        }
        if(i < seq2.size())
        {
            ItemType temp2;
            seq2.get(i, temp2);
            temp.insert(insertpos, temp2);
            insertpos++;
        }
    }
    //Set result equal to the temporary Sequence.
    result = temp;
}


void Sequence::dump() const
{
    Node* p; //Points to the start of the list
    
    for (p = m_head; p->next != m_head; p = p -> next)
    {
        if(p != m_head)
        {
            cerr << p -> data << " ";
        }
    }
    if(p != m_head)
        cerr << p -> data << " ";
    cerr << endl;
    
    Node* s; //Points to the start of the list
    
    for (s = m_head; s->prev != m_head; s = s -> prev)
    {
        if(s != m_head)
        {
            cerr << s -> data << " ";
        }
    }
    if(p != m_head)
        cerr << s -> data << " ";
    cerr << endl;
    cerr << endl;
}



