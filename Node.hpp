//
//  Node.hpp
//  Projekt_AISD4 (B-Tree)
//
//  Created by Michał Boczoń on 20/05/2021.
//

#pragma once
#include <stdio.h>

class Node
{
private:
    int keyAmount;
    bool isLeaf;
    int* keys;
    Node** sons;
    
public:
    Node(int t, bool tf);
    
    int getKeyAmount();
    bool getIsLeaf();
    int* getKeys();
    Node** getSons();
    
    void setIsLeaf(bool tf);
    void setKeyAmount(int n);
    void setKey(int i, int k);
    void setSon(int i, Node* son);
    
    void addKey(int k);
    void addSon(Node* son);
    
    ~Node();
    
};
