//
//  BTree.cpp
//  Projekt_AISD4 (B-Tree)
//
//  Created by Michał Boczoń on 20/05/2021.
//

#include "BTree.hpp"
BTree::BTree(int t){
    root = new Node(t, true);
    this->t = t;
}
Node* BTree::getRoot(){
    return root;
}
std::pair<Node*, int> BTree::search(Node* father, int k){
    if(!root){
        return std::pair<Node*, int> (nullptr, NULL);
    }
    
    if(k == 51){
        
    }
    
    int i = 0;
    
    //increment until either one of the keys is x or there are no more keys in father node
    while((i < father->getKeyAmount()) && (k > father->getKeys()[i])){
        i++;
    }
    
    //check if the key is found and if so return the node and index
    if((i < father->getKeyAmount()) && (k == father->getKeys()[i])){
        return std::pair<Node*, int> (father, i);
    }
    
    //check if this node is leaf and if so end algorith without finding x key
    //else go to the apropriate son node and search x key there
    if(father->getIsLeaf()){
        return std::pair<Node*, int> (nullptr, NULL);
    }
    else{
        return search(father->getSons()[i], k);
    }
}
void BTree::splitChild(Node* father, int i, Node* y){
    Node* z = new Node(t, y->getIsLeaf());
    z->setKeyAmount(t-1);
    
    for(int j=0; j<(t-1); j++){
        z->setKey(j, y->getKeys()[j+t]);
    }
    
    if(!y->getIsLeaf()){
        for(int j=0; j<t; j++){
            z->setSon(j, y->getSons()[j+t]);
        }
    }
    
    y->setKeyAmount(t-1);
    
    for(int j=father->getKeyAmount(); j >= i+1; j--){
        father->setSon(j+1, father->getSons()[j]);
    }
    
    father->setSon(i+1, z);
    
    for(int j=father->getKeyAmount()-1; j >= i; j--){
        father->setKey(j+1, father->getKeys()[j]);
    }
    
    father->setKey(i, y->getKeys()[t-1]);
    father->setKeyAmount(father->getKeyAmount() + 1);
}
void BTree::insertNonFull(Node *father, int k){
    int i = father->getKeyAmount()-1;
    
    if(father->getIsLeaf()){
        while (i >= 0 && k < father->getKeys()[i]) {
            father->setKey(i+1, father->getKeys()[i]);
            i--;
        }
        father->setKey(i+1, k);
        father->setKeyAmount(father->getKeyAmount() + 1);
    }
    else{
        while(i >= 0 && k < father->getKeys()[i]){
            i--;
        }
        
        if(father->getSons()[i+1]->getKeyAmount() == (2*t - 1)){
            splitChild(father, i+1, father->getSons()[i+1]);
            if(k > father->getKeys()[i+1]){
                i++;
            }
        }
        insertNonFull(father->getSons()[i+1], k);
    }
}
void BTree::insert(int k){
    //check if ther is not value k in B-Tree right now
    if(search(root, k) != std::pair<Node*, int> (nullptr, NULL)){
        return;
    }
    
    if (root == nullptr){
        root = new Node(t, true);
        root->getKeys()[0] = k;
        root->setKeyAmount(1);
    }
    else{
        Node* r = root;
        if(root->getKeyAmount() == (2*t - 1)){
            Node* s = new Node(t, false);
            root = s;
            s->setSon(0, r);
            splitChild(s, 0, r);
            insertNonFull(s, k);
        }
        else{
            insertNonFull(r, k);
        }
    }
}
int BTree::findKeyInNode(Node* N, int k){
    int i = 0;
    
    while (i < N->getKeyAmount() && N->getKeys()[i] < k){
        i++;
    }
    
    return i;
}
void BTree::deleteFromLeaf(Node* leaf, int index){
    for(int i=index; i<leaf->getKeyAmount()-1; i++){
        leaf->getKeys()[i] = leaf->getKeys()[i+1];
    }
    
    leaf->setKeyAmount(leaf->getKeyAmount()-1);
}
void BTree::deleteFromNonLeaf(Node* father, int index){
    int k = father->getKeys()[index];
    
    if(father->getSons()[index]->getKeyAmount() >= t){
        int pred = findPredecessor(father, index);
        father->setKey(index, pred);
        remove(father->getSons()[index], pred);
    }
    else if(father->getSons()[index+1]->getKeyAmount() >= t){
        int succ = findSuccessor(father, index);
        father->setKey(index, succ);
        remove(father->getSons()[index+1], succ);
    }
    else{
        merge(father, index);
        remove(father->getSons()[index], k);
    }
}
int BTree::findPredecessor(Node *father, int index){
    Node* tmp = father->getSons()[index];
    
    while (!tmp->getIsLeaf()) {
        tmp = tmp->getSons()[tmp->getKeyAmount()];
    }
    
    return tmp->getKeys()[tmp->getKeyAmount()-1];
}
int BTree::findSuccessor(Node *father, int index){
    Node* tmp = father->getSons()[index + 1];
    
    while (!tmp->getIsLeaf()) {
        tmp = tmp->getSons()[0];
    }
    
    return tmp->getKeys()[0];
}
void BTree::merge(Node *father, int index){
    Node* x = father->getSons()[index];
    Node* y = father->getSons()[index+1];
    
    x->setKey(t-1, father->getKeys()[index]);
    
    for(int i=0; i<y->getKeyAmount(); i++){
        x->setKey(i+t, y->getKeys()[i]);
    }
    
    if(!x->getIsLeaf()){
        for (int i = 0; i <= y->getKeyAmount(); i++){
            x->setSon(i+t, y->getSons()[i]);
        }
    }
    
    for(int i=index; i < father->getKeyAmount()-1; i++){
        father->setKey(i, father->getKeys()[i+1]);
    }
    
    for(int i=index+1; i < father->getKeyAmount(); i++){
        father->setSon(i, father->getSons()[i+1]);
    }
    
    x->setKeyAmount(x->getKeyAmount() + y->getKeyAmount() + 1);
    father->setKeyAmount(father->getKeyAmount() - 1);
    
    delete y;
}
void BTree::fill(Node *father, int index){
    if(index != 0 && father->getSons()[index-1]->getKeyAmount() >= t){
        borrowFromPrev(father, index);
    }
    else if(index != father->getKeyAmount() && father->getSons()[index+1]->getKeyAmount() >= t){
        borrowFromNext(father, index);
    }
    else{
        if(index != father->getKeyAmount()){
            merge(father, index);
        }
        else{
            merge(father, index - 1);
        }
    }
}
void BTree::borrowFromPrev(Node* father, int index) {
    Node* x = father->getSons()[index];
    Node* y = father->getSons()[index - 1];

    for (int i = x->getKeyAmount() - 1; i >= 0; i--){
        x->setKey(i+1, x->getKeys()[i]);
    }

    if (!x->getIsLeaf()) {
        for (int i = x->getKeyAmount(); i >= 0; i--){
            x->setSon(i+1, x->getSons()[i]);
        }
    }
    
    x->setKey(0, father->getKeys()[index-1]);

    if (!x->getIsLeaf()){
        x->setSon(0, y->getSons()[y->getKeyAmount()]);
    }
    
    father->setKey(index-1, y->getKeys()[y->getKeyAmount()-1]);

    x->setKeyAmount(x->getKeyAmount()+1);
    y->setKeyAmount(y->getKeyAmount()-1);

}
void BTree::borrowFromNext(Node* father, int index) {
    Node* x = father->getSons()[index];
    Node* y = father->getSons()[index + 1];
    
    x->setKey(x->getKeyAmount(), father->getKeys()[index]);

    if (!x->getIsLeaf()) {
        x->setSon(x->getKeyAmount()+1, y->getSons()[0]);
    }
    
    father->setKey(index, y->getKeys()[0]);
    
    for(int i = 1; i< y->getKeyAmount(); i++){
        y->setKey(i-1, y->getKeys()[i]);
    }

    if (!y->getIsLeaf()){
        for(int i = 1; i <= y->getKeyAmount(); i++){
            y->setSon(i-1, y->getSons()[i]);
        }
    }

    x->setKeyAmount(x->getKeyAmount()+1);
    y->setKeyAmount(y->getKeyAmount()-1);

}
void BTree::remove(Node* father, int k){
    int index = findKeyInNode(father, k);
    
    if(index < father->getKeyAmount() && father->getKeys()[index] == k){
        if(father->getIsLeaf()){
            deleteFromLeaf(father, index);
        }
        else{
            deleteFromNonLeaf(father, index);
        }
    }
    else{
        if(father->getIsLeaf()){
            return;
        }
        
        bool flag = ((index == father->getKeyAmount()) ? true : false);
        
        if(father->getSons()[index]->getKeyAmount() < t){
            fill(father, index);
        }
        
        if(flag && index > father->getKeyAmount()){
            remove(father->getSons()[index - 1], k);
        }else{
            remove(father->getSons()[index], k);
        }
    }
    
    if(root->getKeyAmount() == 0){
        Node* tmp = root;
        
        if(root->getIsLeaf()){
            root = nullptr;
        }
        else{
            root = root->getSons()[0];
        }
        
        delete tmp;
    }
}
int BTree::convertToInteger(std::string s, int& i){
    std::string number = "";
    int result = 0;
    
    while((int)s[i] >= 48 && (int)s[i] <= 57){
        number += s[i];
        i++;
    }
    
    for(int j=0; j<number.size(); j++){
        result+= ((int)number[j] - 48) * pow(10, number.size() - j - 1);
    }
    
    return result;
}
void BTree::load(Node*father, std::string s, int& index){
    for(;index<s.length(); index++){
        if((int)s[index] >= 48 && (int)s[index] <= 57){
            father->addKey(convertToInteger(s, index));
        }
        else if(s[index] == '('){
            index++;
            Node* newNode = new Node(t, true);
            father->addSon(newNode);
            load(newNode, s, index);
        }
        else if(s[index] == ')'){
            break;
        }
    }
}
void BTree::printTree(Node *father){
    printf("( ");
    if(father->getIsLeaf()){
        for(int i=0; i<father->getKeyAmount(); i++)
            printf("%d ", father->getKeys()[i]);
    }
    else{
        for(int i=0; i<=father->getKeyAmount(); i++){
            printTree(father->getSons()[i]);
            if(i < father->getKeyAmount()){
                printf("%d ", father->getKeys()[i]);
            }
        }
    }
    printf(") ");
}
void BTree::save(){
    printf("%d\n", t);
    printTree(root);
    printf("\n");
}
void BTree::printValuesInIncreasingOrder(Node* father){
    //if node is leaf just print all of its keys
    if(father->getIsLeaf()){
        for(int i=0; i<father->getKeyAmount(); i++)
            printf("%d ", father->getKeys()[i]);
    }//otherwise call print function for all of node's sons and after each
    //print the key before the next one
    else{
        for(int i=0; i<=father->getKeyAmount(); i++){
            printValuesInIncreasingOrder(father->getSons()[i]);
            if(i < father->getKeyAmount()){
                printf("%d ", father->getKeys()[i]);
            }
        }
    }
}
int BTree::calculateAccesses(int k){
    int acc=1;
    int i=0;
    Node* tmp = root;
    
    while(tmp->getKeys()[i] != k){
        while((i < tmp->getKeyAmount()) && (tmp->getKeys()[i] < k)){
            i++;
        }
        
        if(i < tmp->getKeyAmount() && tmp->getKeys()[i] == k){
            return acc;
        }
        
        if(tmp->getIsLeaf()){
            return acc;
        }else{
            tmp = tmp->getSons()[i];
            i=0;
            acc++;
        }
    }
    
    return acc;
}
int BTree::nextOccurance(std::vector<int> queries, int k, int index){
    if(index == queries.size()-1){
        return -1;
    }
    
    for(int i = (index+1); i<queries.size(); i++){
        if(queries[i] == k){
            return (i - index);
        }
    }
    
    return -1;
}
void BTree::printCacheImpact(int capacity, std::string s){
    
    std::vector<int> cache;
    bool isInCache = false;
    int acc;
    
    
    
    // FIFO cache policy
    int noCacheSum = 0, cacheSum = 0;

    
    int q;
    for(int i=0; i<s.length(); i++){
        if(s[i] >= 48 && s[i] <=57){
            isInCache = false;
            q = convertToInteger(s, i);
            acc = calculateAccesses(q);
            noCacheSum += acc;
            
            for(int j=0; j < cache.size(); j++){
                if(cache[j] == q){
                    isInCache = true;
                    break;
                }
            }
            
            if(!isInCache){
                if(cache.size() < capacity){
                    cache.push_back(q);
                }
                else{
                    cache.erase(cache.begin());
                    cache.push_back(q);
                }
                cacheSum += acc;
            }
        }
    }
    
    //  Bélády's algorithm (clairvoyant alorithm) - ANOTHER CACHE POLICY
    //
    //  Since we know all the queries in occurrence order, when needed we can discard a key from cache
    //  that will not be needed for the longest time (the furthest from actual query).
    
    //  Clear cache from previous policy algorithm.
    cache.clear();
    
    std::vector<int> queries;
    int myCacheSum = 0;
    
    //  Collect all the queries from given string into vector.
    for(int i=0; i<s.length(); i++){
        if(s[i] >= 48 && s[i] <= 57){
            queries.push_back(convertToInteger(s, i));
        }
    }
    
    //  Calculate clairvoyant cache policy impact.
    for(int i=0; i<queries.size(); i++){
        isInCache = false;
        
        for(int j=0; j < cache.size(); j++){
            if(cache[j] == queries[i]){
                isInCache = true;
                break;
            }
        }
        
        if(!isInCache){
            acc = calculateAccesses(queries[i]);
            
            if(cache.size() < capacity){
                cache.push_back(q);
                myCacheSum += acc;
            }
            else{
                int maxDistance = 0;
                int nextOcc;
                
                // Finding the maximum distance of occurance in cache memory.
                for(int j = 0; j<cache.size(); j++){
                    nextOcc = nextOccurance(queries, cache[j], i);
                    if(nextOcc > maxDistance){
                        maxDistance = nextOcc;
                    }
                }
                
                // Swaping values in cache if the next occurance of actual query is less than maximum occurance.
                // Otherwise do nothing.
                if(nextOccurance(queries, queries[i], i) < maxDistance){
                    for(int j=0; j<cache.size(); j++){
                        if(nextOccurance(queries, cache[j], i) == maxDistance){
                            cache[j] = queries[i];
                            myCacheSum += acc;
                            break;
                        }
                    }
                }
            }
        }
    }
    
    
    printf("NO CACHE: %d CACHE: %d\n", noCacheSum, cacheSum);
    //printf("CLAIRVOYANT POLICY: %d\n", myCacheSum);
}
BTree::~BTree(){
    delete root;
}
