//
//  Sequence.cpp
//  project2
//
//  Created by Katie Cai on 1/27/17.
//  Copyright © 2017 Katie Cai. All rights reserved.
//

#include "Sequence.h"
#include <iostream>

Sequence::Sequence() : m_size(0) {
    dummyNode = new Node;
    head = dummyNode;
    dummyNode->m_prev = dummyNode;
    dummyNode->m_next = dummyNode;
}

Sequence::Sequence(const Sequence& other) : m_size(0) {
    //create new head + dummy node
    Node* dummyNode = new Node;
    head = dummyNode;
    dummyNode->m_prev = dummyNode;
    dummyNode->m_next = dummyNode;
    
    Node* p;
    int i;

    //loop through items in other sequence, and add them to the end of this sequence
    for (i = 0, p = other.head->m_next; p != other.head; i++, p = p->m_next) {
        insert(i, p->m_data);
    }
    
}

Sequence& Sequence::operator=(const Sequence& rhs) {
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}

Sequence::~Sequence() {
    //delete every node - starting from the back
    while (size() > 0) {
        erase(size()-1);
    }
    
    //delete dummy node!!
    delete head;
}

bool Sequence::empty() const {
    if (m_size == 0)
        return true;
    return false;
}

int Sequence::size() const {
    return m_size;
}

bool Sequence::insert(int pos, const ItemType& value) {
    if (pos < 0)
        return false;
    
    int i;
    Node* p;
    
    //stop when at the object with position pos
    for (i = 0, p = head->m_next; i != pos; i++, p = p->m_next) {
        ;
    }
    
    Node* newNode = new Node;
    newNode->m_data = value;
    //make the new node point to the item at pos and the item at pos's m_prev
    newNode->m_next = p;
    newNode->m_prev = p->m_prev;
    //make newNode's m_prev point to newNode & newNode's m_next point to newNode
    p->m_prev->m_next = newNode;
    p->m_prev = newNode;
    
    m_size++;
    
    return true;
}

int Sequence::insert(const ItemType& value) {
    int i;
    Node* p;
    
    //loop until you reach the pos where value <= the item at pos, or the end
    for (i = 0, p = head->m_next; p != head && value > p->m_data; i++, p = p->m_next) {
        ;
    }
    
    Node* newNode = new Node;
    newNode->m_data = value;
    newNode->m_next = p;
    newNode->m_prev = p->m_prev;
    p->m_prev->m_next = newNode;
    p->m_prev = newNode;
    m_size++;
    
    return i;
}

bool Sequence::erase(int pos) {
    if (pos >= size() || pos < 0)
        return false;
    
    int i;
    Node* p;
    
    //stop as position pos
    for (i = 0, p = head->m_next; p != head && i != pos; i++, p = p->m_next) {
        ;
    }
    
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;
    m_size--;
    
    return true;
}

int Sequence::remove(const ItemType& value) {
    int i;
    Node* p;
    int removed = 0;
    
    p = head->m_next;
    i = 0;
    
    while (p != head) {
        
        if (p->m_data == value) {
            removed++;
            //move pointer first so you don't have p pointing to a deleted object
            p = p->m_next;
            erase(i);
            //don't increment i here - just in case next item also == value
        }
        
        else {
            p = p->m_next;
            i++;
        }
        
    }
    
    return removed;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (pos >= size() || pos < 0)
        return false;
    
    int i;
    Node* p;
    
    //loop through list until at specified position
    for (i = 0, p = head->m_next; i != pos; i++, p = p->m_next) {
        ;
    }
    
    value = p->m_data;
    
    return true;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (pos >= size() || pos < 0)
        return false;
    
    int i;
    Node* p;
    
    //loop through list until at specified position
    for (i = 0, p = head->m_next; i != pos; i++, p = p->m_next) {
        ;
    }
    
    p->m_data = value;
    
    return true;
}

int Sequence::find(const ItemType& value) const {
    int i;
    Node* p;
    
    //loop through list until we're at the position where m_data = value
    for (i = 0, p = head->m_next; p != head && p->m_data != value; i++, p = p->m_next) {
        ;
    }
    
    if (p == head) {
        i = -1;
    }
    
    return i;
}

void Sequence::swap(Sequence& other) {
    //swap size & head pointers
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    Node* temphead = head;
    head = other.head;
    other.head = temphead;
}

int subsequence(const Sequence& seq1, const Sequence& seq2) {
    if (seq2.empty() || seq2.size() > seq1.size())
        return -1;
    
    int smaller = 0;
    int bigger = 0;
    int count = 0;
    bool incrementsmaller = true;
    
    ItemType valMin;
    ItemType valMax;
    
    while (smaller < seq2.size()) {
        incrementsmaller = true;
        seq2.get(smaller, valMin);
        
        while (bigger < seq1.size()) {
            seq1.get(bigger, valMax);
            if (valMin == valMax) {
                count++;
                bigger++;
                break;
            }
            else if (count > 0) {
                //move back to pos 0 of seq 2 & reset count
                incrementsmaller = false;
                smaller -= count;
                count = 0;
                break;
            }
            bigger++;
        }
        
        if (count == seq2.size()) {
            //position in seq1 - size of seq2 gives us the position where seq2 starts in seq1
            return bigger-seq2.size();
        }
        if (incrementsmaller == true)
        //don't increment if count was set back to 0
            smaller++;
        
    }
    
    return -1;

}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
    Sequence max;
    Sequence min;
    Sequence tempresult;
    
    if (seq1.size() >= seq2.size()) {
        max = seq1;
        min = seq2;
    }
    else  {
        max = seq2;
        min = seq1;
    }
    
    ItemType valMin;
    ItemType valMax;
    
    int i = 0;
    int j = 0;
    int k = 0;
    //keeps track of when to insert an item from the bigger sequence
    bool bigger = true;
    int cycle = 0;
    
    while (i < seq1.size()+seq2.size()) {
        if (bigger == true) {
            bigger = false;
            //i is 1 position ahead of j
            j = i/2;
            max.get(j, valMax);
            while (cycle < 1) {
                tempresult.insert(i, valMax);
                cycle++;
            }
        }
        else {
            bigger = true;
            //i is 2 positions ahead of k
            k = i/2;
            if (k == min.size()) {
                break;
            }
            min.get(k, valMin);
            while (cycle < 2) {
                tempresult.insert(i, valMin);
                cycle++;
            }
        }
        
        //end of a cycle means we've added 1 item from seq1 and 1 item from seq 2
        if (bigger == true)
            cycle = 0;
        i++; //move along result
    }
    
    //if we've gone through the smaller sequence completely - add the rest of the elements of the bigger sequence to the end
    j++;
    while (j < max.size()) {
        max.get(j, valMax);
        tempresult.insert(i, valMax);
        i++;
        j++;
    }
    
    //if either sequence was empty - return the other sequence
    if (seq1.empty()) {
        tempresult = seq2;
    }
    else if (seq2.empty()) {
        tempresult = seq1;
    }
    
    result = tempresult;
}

void Sequence::dump() const {
    ItemType val;
    for (int i = 0; i < size(); i++) {
        get(i, val);
        std::cerr << val << " ";
    }
    std::cerr << std::endl;
}

