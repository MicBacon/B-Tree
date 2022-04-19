//
//  main.cpp
//  Projekt_AISD4 (B-Tree)
//
//  Created by Michał Boczoń on 20/05/2021.
//

#include <iostream>
#include "Node.hpp"
#include "BTree.hpp"

int main(int argc, const char * argv[]) {
    BTree* myTree = new BTree(3);
    int x;
    char c;
    std::string s;
    
    while(std::cin>>c){
        if(c == 'I'){
            scanf("%d", &x);
            myTree = new BTree(x);
        }
        else if(c == 'A'){
            scanf("%d", &x);
            myTree->insert(x);
        }
        else if(c == '?'){
            scanf("%d", &x);
            if(myTree->search(myTree->getRoot(), x) !=
               std::pair<Node*, int> (nullptr, NULL)){
                printf("%d +\n", x);
            }else{
                printf("%d -\n", x);
            }
        }
        else if(c == 'P'){
            myTree->printValuesInIncreasingOrder(myTree->getRoot());
            printf("\n");
        }
        else if(c == 'L'){
            int index = 1;
            scanf("%d\n", &x);
            std::getline(std::cin, s);
            myTree = new BTree(x);
            myTree->load(myTree->getRoot(), s, index);
        }
        else if(c == 'S'){
            myTree->save();
        }
        else if(c == 'R'){
            scanf("%d", &x);
            std::pair<Node*, int> result = myTree->search(myTree->getRoot(), x);
            
            if(result !=
               std::pair<Node*, int> (nullptr, NULL)){
                myTree->remove(myTree->getRoot(), x);
            }
        }
        else if(c == 'C'){
            scanf("%d", &x);
            std::getline(std::cin, s);
            myTree->printCacheImpact(x, s);
        }
        else if(c == 'X'){
            break;
        }
    }
    return 0;
}
