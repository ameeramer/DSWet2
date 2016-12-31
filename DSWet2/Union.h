//
//  Union.h
//  DSWet2
//
//  Created by Ameer Amer on 30/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//

#ifndef Union_h
#define Union_h

template<class KeyType, class ValueType>
struct SetInfo;

template<class KeyType, class ValueType>
struct Node;

template<class KeyType, class ValueType>
struct Node{
    int key;
    ValueType* data;
    struct Node* parent;
    struct SetInfo<KeyType, ValueType>* setInfo;
};

template<class KeyType, class ValueType>
struct SetInfo{
    int setNum;
    struct Node<KeyType, ValueType>* rootOfSet;
    int numOfElements;
};

template <class KeyType, class ValueType>
class UnionFind {
    struct Node<KeyType, ValueType>** arrayOfNodes;
    struct SetInfo<KeyType,ValueType>** arrayOfSets;
    
public:
    UnionFind(int n, int keys[], ValueType* values[]){
        arrayOfNodes = new struct Node<KeyType,ValueType>*[n];
        arrayOfSets = new struct SetInfo<KeyType,ValueType>*[n];
        for (int i=0; i<n; i++) {
            arrayOfNodes[i] = new struct Node<KeyType,ValueType>;
            arrayOfNodes[i]->key = keys[i];
            arrayOfNodes[i]->data = values[i];
            arrayOfNodes[i]->parent = arrayOfNodes[i];
            arrayOfNodes[i]->setInfo = new SetInfo<KeyType, ValueType>;
            arrayOfNodes[i]->setInfo->setNum = i;
            arrayOfNodes[i]->setInfo->rootOfSet = arrayOfNodes[i];
            arrayOfNodes[i]->setInfo->numOfElements = 1;
            arrayOfSets[i] = arrayOfNodes[i]->setInfo;
        }
    }
    
    struct Node<KeyType,ValueType>* findAux(struct Node<KeyType, ValueType>* node){
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
            delete arrayOfSets[set1];
            arrayOfSets[set1] = NULL;
        }
        else{
            arrayOfSets[set2]->rootOfSet->parent = arrayOfSets[set1]->rootOfSet;
            arrayOfSets[set1]->numOfElements += arrayOfSets[set2]->numOfElements;
            delete arrayOfSets[set2];
            arrayOfSets[set2] = NULL;
        }
    }
};


#endif /* Union_h */
