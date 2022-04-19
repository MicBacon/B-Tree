//
//  Node.cpp
//  Projekt_AISD4 (B-Tree)
//
//  Created by Michał Boczoń on 20/05/2021.
//

#include "Node.hpp"

Node::Node(int t, bool tf){
    isLeaf = tf;
    keys = new int[2*t - 1];
    sons = new Node *[2*t];
    keyAmount = 0;
}
int Node::getKeyAmount(){
    return keyAmount;
}
bool Node::getIsLeaf(){
    return isLeaf;
}
Node** Node::getSons(){
    return sons;
}
int* Node::getKeys(){
    return keys;
}
void Node::setIsLeaf(bool tf){
    isLeaf = tf;
}
void Node::setKeyAmount(int n){
    keyAmount = n;
}
void Node::setKey(int i, int k){
    keys[i] = k;
}
void Node::setSon(int i, Node *son){
    sons[i] = son;
}
Node::~Node(){
    for(int i=0; i<=keyAmount; i++){
        sons[i] = nullptr;
    }
    if(!isLeaf){
        delete[] *sons;
    }
    delete[] keys;
}
void Node::addKey(int k){
    int* tmp = keys;
    
    keyAmount++;
    
    keys = new int[keyAmount];
    
    for(int i=0; i<keyAmount-1; i++){
        keys[i] = tmp[i];
    }
    keys[keyAmount-1] = k;
    
    delete tmp;
}
void Node::addSon(Node *son){
    if(isLeaf){
        isLeaf=false;
        
        sons = new Node*[1];
        
        sons[0] = son;
        
        return;
    }
    
    Node** tmp = sons;
    
    sons = new Node*[keyAmount+1];
    
    for(int i=0; i<keyAmount; i++){
        sons[i] = tmp[i];
    }
    sons[keyAmount] = son;
    
    delete tmp;
}
