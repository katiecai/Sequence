//
//  Sequence.hpp
//  project2
//
//  Created by Katie Cai on 1/27/17.
//  Copyright © 2017 Katie Cai. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <stdio.h>
#include <iostream>
#include <string> 

typedef std::string ItemType;

class Sequence
{
public:
    Sequence();
    Sequence(const Sequence& other);
    Sequence& operator=(const Sequence& rhs);
    ~Sequence();
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
private:
    struct Node {
        ItemType m_data;
        Node* m_prev;
        Node* m_next;
    };
    int m_size;
    Node* head;
    Node* dummyNode;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif /* Sequence_hpp */
