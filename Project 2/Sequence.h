//
//  Sequence.h
//  C32_Project2
//
//  Created by Tran on 4/17/19.
//  Copyright © 2019 Tran. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h
#include <iostream>
#include <string>
using namespace std;
using ItemType = string;

class Sequence
{
public:
    Sequence();
    ~Sequence ();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& other);
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    struct Node
    {
        ItemType data;
        Node* next;
        Node* prev;
    };
    Node* m_head;
    int m_size;
    Node* Dummy;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif /* Sequence_h */
