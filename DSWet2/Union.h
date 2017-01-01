//
//  Union.h
//  DSWet2
//
//  Created by Ameer Amer on 30/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//

#ifndef Union_h
#define Union_h

#include <iostream>

struct SetInfo;

struct Node;

struct Node{
    int key;
    struct Node* parent;
    struct SetInfo* setInfo;
};

struct SetInfo{
    int setNum;
    struct Node* rootOfSet;
    int numOfElements;
    int otherData;
};

class UnionFind {
    struct Node** arrayOfNodes;
    struct SetInfo** arrayOfSets;
    int size;
    
public:
    UnionFind(int n, int* data){
        size = n;
        arrayOfNodes = new struct Node*[n];
        arrayOfSets = new struct SetInfo*[n];
        for (int i=0; i<n; i++) {
            arrayOfNodes[i] = new struct Node;
            arrayOfNodes[i]->key = i;
            arrayOfNodes[i]->parent = arrayOfNodes[i];
            arrayOfNodes[i]->setInfo = new SetInfo;
            arrayOfNodes[i]->setInfo->setNum = i;
            arrayOfNodes[i]->setInfo->rootOfSet = arrayOfNodes[i];
            arrayOfNodes[i]->setInfo->numOfElements = 1;
            arrayOfNodes[i]->setInfo->otherData = data[i];
            arrayOfSets[i] = arrayOfNodes[i]->setInfo;
        }
    }
    
    struct Node* findAux(struct Node* node){
        if(node->parent != node){
            node->parent = findAux(node->parent);
        }
        return node->parent;
    }
    
    int find(int key){
        return (findAux(arrayOfNodes[key]))->setInfo->setNum;
    }
    
    void Union(int key1, int key2){
        int set1 = find(key1);
        int set2 = find(key2);
        if(set1==set2) return;
        
        if(arrayOfSets[set1]->numOfElements <= arrayOfSets[set2]->numOfElements){
            arrayOfSets[set1]->rootOfSet->parent = arrayOfSets[set2]->rootOfSet;
            arrayOfSets[set2]->numOfElements += arrayOfSets[set1]->numOfElements;
            arrayOfSets[set2]->otherData += arrayOfSets[set1]->otherData;
            delete arrayOfSets[set1];
            arrayOfSets[set1] = NULL;
        }
        else{
            arrayOfSets[set2]->rootOfSet->parent = arrayOfSets[set1]->rootOfSet;
            arrayOfSets[set1]->numOfElements += arrayOfSets[set2]->numOfElements;
            arrayOfSets[set1]->otherData += arrayOfSets[set2]->otherData;
            delete arrayOfSets[set2];
            arrayOfSets[set2] = NULL;
        }
    }
    
    int sizeOfSet(int key){
        int set = find(key);
        return arrayOfSets[set]->numOfElements;
    }
    
    int dataOfSet(int key){
        int set = find(key);
        return arrayOfSets[set]->otherData;
    }
    
    ~UnionFind(){
        for(int i=0; i<size; i++){
            delete arrayOfNodes[i];
            delete arrayOfSets[i];
        }
        delete[] arrayOfNodes;
        delete[] arrayOfSets;
    }
};


#endif /* Union_h */
