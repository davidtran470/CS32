//
//  HashTable.h
//  CompressionOppression
//
//  Created by Tran on 5/30/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h
#include <string>
#include <vector>
using namespace std;

extern int SEQUENCE_LENGTH;
//Choose Prime Number to disrupt patterns.
const int DEFAULT_Table_Size = 57251;
class HashTable
{
public:
    HashTable(int size = DEFAULT_Table_Size);
    //HouseKeepingFunction
    ~HashTable();
    //Converts item in a hash value
    int hashfunction(string item) const;
    void additem(string item, int offset);
    //Returns offset if we can find the item. If we do not find the item return -1.
    int find(const string& item, const string& oldstr, const string& newstr, const int& offset, int& size) const;


private:
    //Nodes hold the item and its corresponding offset.
    struct Node
    {
        string item;
        int offset;
        Node* next;
    };
    vector<Node*> table;
    int m_size;
};

#endif /* HashTable_h */
