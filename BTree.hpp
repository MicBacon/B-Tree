//
//  BTree.hpp
//  Projekt_AISD4 (B-Tree)
//
//  Created by Michał Boczoń on 20/05/2021.
//

#pragma once

#include <stdio.h>
#include "Node.hpp"
#include <vector>
#include <string>
#include <cmath>


class BTree
{
private:
    int t;
    Node* root;
public:
    BTree(int t);
        
    Node* getRoot();
    
    std::pair<Node*, int> search(Node* father, int k);
    int findKeyInNode(Node* N, int k);
    int findPredecessor(Node* father, int index);
    int findSuccessor(Node* father, int index);
    
    void splitChild(Node* father, int i, Node* y);
    void insert(int k);
    void insertNonFull(Node* father, int k);
    
    void remove(Node* father, int k);
    void deleteFromLeaf(Node* leaf, int index);
    void deleteFromNonLeaf(Node* father, int index);

    void merge(Node* father, int index);
    void fill(Node* father, int index);
    void borrowFromPrev(Node* father, int index);
    void borrowFromNext(Node* father, int index);
    
    void load(Node*father, std::string s, int& index);
    void save();
    
    int convertToInteger(std::string s, int& i);
    int calculateAccesses(int k);
    int nextOccurance(std::vector<int> queries, int k, int index);
    void printValuesInIncreasingOrder(Node* father);
    void printTree(Node* father);
    void printCacheImpact(int capacity, std::string s);
    
    ~BTree();
    
};
