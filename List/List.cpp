//
//  List.cpp
//  Projekt_AISD2
//
//  Created by Michał Boczoń on 01/04/2021.
//

#include "List.hpp"
#include "Node.hpp"
#include <iostream>

List::List(){
    beg = nullptr;
    end = nullptr;
    this->size = 0;
}
Node* List::getBeg(){
    return beg;
}
Node* List::getEnd(){
    return end;
}
size_t List::getSize() const{
    return size;
}
void List::setBeg(Node *N){
    beg = N;
}
void List::setEnd(Node *N){
    end = N;
}
//dodawanie węzła na początek listy
void List::addBeg(int value){
    if(!beg){
        Node* newNode = new Node(value);
        beg = end = newNode;
        beg->setNext(end);
        beg->setPrev(end);
        end->setNext(beg);
        end->setPrev(beg);
        size++;
    }else{
        Node* newNode = new Node(value, end, beg);
        beg->setPrev(newNode);
        end->setNext(newNode);
        beg = newNode;
        size++;
    }
}
//dodawanie węzła na koniec listy
void List::addEnd(int value){
    if(!beg){
        Node* newNode = new Node(value);
        beg = end = newNode;
        beg->setNext(end);
        beg->setPrev(end);
        end->setNext(beg);
        end->setPrev(beg);
        size++;
    }else{
        Node* newNode = new Node(value, end, beg);
        end->setNext(newNode);
        beg->setPrev(newNode);
        end = newNode;
        size++;
    }
   
}
void List::addBefore(Node *N, int value){
    Node* newNode = new Node(value);
    
    N->getPrev()->setNext(newNode);
    newNode->setPrev(N->getPrev());
    newNode->setNext(N);
    N->setPrev(newNode);
    
    N = newNode;
    size++;
    
    if(beg->getPrev() != end){
        beg = beg->getPrev();
    }
    if(end->getNext() != beg){
        end = end->getNext();
    }
}
//usunięcie pierwszego elementu
void List::delBeg(){
    if(!beg){return;}
    
    if(beg == end){
        delete beg;
        beg = end = nullptr;
    }else{
        Node* tmp = beg->getNext();
        delete beg;
        
        beg = tmp;
        beg->setPrev(end);
        end->setNext(beg);
    }
    size--;
}
//usunięcie ostatniego elementu
void List::delEnd(){
    if(!beg){return;}
    
    if(beg == end){
        delete end;
        beg = end = nullptr;
    }else{
        Node* tmp = end->getPrev();
        delete end;
        
        end = tmp;
        end->setNext(beg);
        beg->setPrev(end);
    }
    size--;
}
//usuwanie określonego elementu z listy
void List::delNode(Node *N){
    if(N->getNext() == N){ delBeg(); return;}
    
    (N->getPrev())->setNext(N->getNext());
    (N->getNext())->setPrev(N->getPrev());
    
    size--;
    
    delete N;
}
//drukowanie listy od beg do end
void List::printForward() const{
    if(!beg){ std::cout<<"NULL"<<std::endl; return;}
    
    Node* tmp = end;
    while(tmp->getNext() != end){
        std::cout << tmp->getNext()->getValue() << " ";
        tmp = tmp->getNext();
    }
    
    
    std::cout << tmp->getNext()->getValue() << std::endl;
}
//drukowanie list od end do beg
void List::printBackward() const{
    if(!beg){ std::cout<<"NULL"<<std::endl; return;}
    
    Node* tmp = beg;
    while(tmp->getPrev() != beg){
        std::cout << tmp->getPrev()->getValue() << " ";
        tmp = tmp->getPrev();
    }
    
    std::cout << tmp->getPrev()->getValue() << std::endl;
}
