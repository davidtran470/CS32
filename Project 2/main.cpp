//
//  main.cpp
//  C32_Project2
//
//  Created by Tran on 4/17/19.
//  Copyright © 2019 Tran. All rights reserved.
//

//#include <iostream>
//#include <cassert>
//#include "Sequence.h"

//int main()
//{
//    //Insert & Find & Set & Get & Erase & Remove Implementation Implementation Test
////=====================================//
//    Sequence e;
//    assert(e.empty() == true); //Check that e is empty.
//    assert(e.insert(1) == 0); //Insert into an empty list
//    assert(e.insert(2) == 1); //Insert into the end of the list
//    assert(e.insert(3) == 2); //Insert into the end of the list
//    assert(e.insert(4) == 3); //Insert into the end of the list
//    assert(e.insert(5) == 4); //Insert into the end of the list
//    assert(e.insert(0) == 0); //Insert into the beginning of the list
//    assert(e.insert(1) == 1); //Insert into the 1 index of the list
//    assert(e.size() == 7); //Size is correctly implemented
//    assert(e.find(0) == 0); //0 is in the 0th index
//    assert(e.find(2) == 3); //2 is in the 3rd index.
//    assert(e.find(5) == 6); //5 is in the last index (6th)
//    ItemType temp;
//    assert(e.set(0, 10) == true); //Set first element to 10
//    assert(e.get(0, temp) == true);
//    assert(temp == 10); // Ensure that the get function works properly
//    assert(e.set(6, 100) == true); //Set first element to 100
//    assert(e.get(6, temp) == true);
//    assert(temp == 100); //Ensure that get function works for edge cases
//    assert(e.set(7,100) == false); //Out of bounds
//    e.dump();
//    assert(e.remove(1) == 2); //Removes two 1's from the linked list
//    assert(e.remove(2) == 1); //removes one 2 from the linked list
//    assert(e.size() == 4); //Size is reduced to 4
//    assert(e.erase(0) == true); // Erase the leading node
//    assert(e.erase(2) == true); //Erase last node
//    assert(e.find(10) == -1);
//    assert(e.find(100) == -1);
//    e.dump();
//
//    //Insert with Position
////=====================================//
//    Sequence d;
//    assert(d.insert(0,1) == 0); //Insert into an empty list
//    assert(d.insert(1,2) == 1); //Insert into the end of the list
//    assert(d.insert(2,3) == 2); //Insert into the end of the list
//    assert(d.insert(3,4) == 3); //Insert into the end of the list
//    assert(d.insert(4,5) == 4); //Insert into the end of the list
//    assert(d.insert(0,0) == 0); //Insert into the beginning of the list
//    assert(d.insert(1, 1) == 1); //Insert into the 1 index of the list
//    assert(d.insert(8, 0) == -1); //Cheeck that insert does not work out of bounds
//    d.dump();
//
//
//    //Swap function
////=====================================//
//    Sequence c;
//    c.insert(1);
//    c.insert(2);
//    c.insert(3);
//    c.insert(4);
//    c.insert(5);
//    Sequence b;
//    b.insert(1);
//    c.swap(b);
//    assert(c.size() == 1); //Check that sizes have swapped
//    assert(b.size() == 5);
//    assert(c.find(5) == -1); //Check that data has swapped too
//    assert(c.find(4) == -1);
//    c.insert(1); //Check that manipulation to one does not affect the other.
//    assert(c.size() == 2);
//    assert(b.size() == 5);
//
//
//
//    //Copy Constructor Test
////=====================================//
//    Sequence v;
//    v.insert(1);
//    v.insert(2);
//    v.insert(3);
//    v.insert(4);
//    v.insert(5);
//    v.dump();
//    Sequence t = v; //Test copy constructor
//    t.dump();
//    t.erase(0); //Test that manipulating d does not manipulate c.
//    t.erase(0);
//    assert(t.size() == 3); //Check that only size of t changes
//    assert(v.size() == 5);
//    t.dump();
//    v.dump();
//    v.insert(2);
//    v.insert(3);
//    v.insert(4);
//    v.insert(5);
//    assert(t.size() == 3);
//    assert(v.size() == 9); //Check that size of v changes
//
//    //Assignment Operator Test
////=====================================//
//    Sequence f;
//    f.insert(1);
//    f.insert(2);
//    f.insert(3);
//    f.insert(4);
//    f.insert(5);
//    Sequence g;
//    g.insert(10);
//    g.insert(10);
//    g.insert(10);
//    g.insert(10);
//    g.insert(10);
//    f.dump();
//    g.dump();
//    g = f; // Test Assignment Operator
//    assert(g.find(10) == -1); //Ensure that g no longer has its original values
//    f.dump();
//    g.dump();
//    g.insert(10); //Test that changing g does not affect f
//    assert(g.size() == 6);
//    assert(f.size() == 5);
//    f.dump();
//    g.dump();
//    f = f; //Test for aliasing.
//    assert(f.find(2) == 1);
//
////Subsequence Function Test
////=====================================//
//    Sequence y;
//    y.insert(0, 32);
//    y.insert(0, 8);
//    y.insert(0, 29);
//    y.insert(0, 17);
//    y.insert(0, 63);
//    y.insert(0, 17);
//    y.insert(0, 42);
//    y.insert(0, 63);
//    y.insert(0, 21);
//    y.insert(0, 30);
//    g.dump();
//    Sequence h;
//    h.insert(0, 29);
//    h.insert(0, 17);
//    h.insert(0, 63);
//    h.dump();
//    assert(subsequence(y, h) == 5); //The consecutive terms of sequence h occcur in sequence g at position 5.
//    Sequence i;
//    i.insert(0, 29);
//    i.insert(0, 63);
//    i.insert(0, 17);
//    i.dump();
//    assert(subsequence(g, i) == -1); //The consecutive terms of sequence i do not appear in sequence g.
//    Sequence j;
//    Sequence k;
//    assert(subsequence(g, j) == -1); //If seq2 is empty, the function returns -1;
//    assert(subsequence(j, g) == -1); //If seq1 is empty, the function return -1;
//    assert(subsequence(h, g) == -1); //If seq2 is larger than seq1, the function returns -1;
//    Sequence l;
//    l.insert(0, 29);
//    l.insert(0, 63);
//    l.insert(0, 17);
//    l.insert(0, 17);
//    l.insert(0, 100);
//    l.insert(0, 63);
//    l.insert(0, 17);
//    l.insert(0, 100);
//    l.insert(0, 63);
//    l.insert(0, 17);
//    l.dump();
//    assert(subsequence(l, i) == 7); //The consecutive terms of sequence i occcur in sequence l at position 7.
//    Sequence m;
//    m.insert(0, 29);
//    m.insert(0, 63);
//    m.insert(0, 17);
//    i.dump();
//    assert(subsequence(i, m) == 0); //Seq1 and seq2 are equal. Therefore, consecutive terms begin at position 0.
//    assert(subsequence(i, i) == 0); //Because i is the same, consecutive terms begin at position 0.
//    l.dump();
//    Sequence u;
//    u.insert(0, 29);
//    u.insert(0, 63);
//    assert(subsequence(l,u) == 8);
//
//    //Interleave Function Test
////=====================================//
//    interleave(l, j, k); //Since j is empty, k will be equal to l.
//    assert(k.size() == l.size());
//    int temp2 = l.size();
//    interleave(l, l, l); //Check for aliase case. L should be twice as lone as it was originally.
//    assert(l.size() == 2*temp2);
//    interleave(k, m, j); //Size of j should be a combination of the size of k and m.
//    assert(j.size() == k.size() + m.size());
//    assert(j.find(29) == 5); //29 should be in the 5th index of j due to contribution of m.
//    l.dump();
//    return 0;
//}
//
#include "Sequence.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence s;
    assert(s.insert(0, "lavash") == 0);
    assert(s.insert(0, "tortilla") == 0);
    assert(s.size() == 2);
    ItemType x = "injera";
    assert(s.get(0, x)  &&  x == "tortilla");
    assert(s.get(1, x)  &&  x == "lavash");
}

int main()
{
    test();
    cout << "Passed all tests" << endl;
}
