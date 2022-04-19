#pragma once
#include <stdio.h>
#include "Node.hpp"

class List
{
private:
    Node *beg, *end;
    size_t size;
public:
    
    List();
    
    Node* getBeg();
    Node* getEnd();
    size_t getSize() const;
    
    void setBeg(Node *N);
    void setEnd(Node *N);
    
    void addFirstElement(int value);
    void addBeg(int value);
    void addEnd(int value);
    void addBefore(Node* N, int value);
    void delBeg();
    void delEnd();
    void delNode(Node *N);
    void printForward() const;
    void printBackward() const;
    
};
