//
//  HashTable.h
//  DSWet2
//
//  Created by Ameer Amer on 31/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
template <class T>
struct ListNode {
    int key;
    T* data;
    struct ListNode* next;
};

template <class T>
class List {
    struct ListNode<T>* head;
    
public:
    List(){
        head = new struct ListNode<T>;
        head->key = -1;
        head->data = NULL;
        head->next = NULL;
    }
    
    void Insert(int key, T* data){
        struct ListNode<T>* newNode = new struct ListNode<T>;
        newNode->key = key;
        newNode->data = data;
        newNode->next = head->next;
        head->next = newNode;
    }
    
    void deleteElement(int key){
        struct ListNode<T>* curr = head;
        while(curr->next){
            if(curr->next->key == key){
                struct ListNode<T>* toDelete = curr->next;
                curr->next = toDelete->next;
                delete (toDelete);
                break;
            }
            curr = curr->next;
        }
    }
    
    T* getElement(int key){
        struct ListNode<T>* curr = head->next;
        while(curr){
            if(curr->key == key){
                return curr->data;
            }
            curr = curr->next;
        }
        return NULL;
    }
    
    struct ListNode<T>* getFirstNode(){
        return head->next;
    }
    
    ~List(){
        struct ListNode<T>* curr = head;
        struct ListNode<T>* toDelete;
        while(curr){
            toDelete = curr;
            curr = curr->next;
            delete(toDelete);
        }
    }
};

template <class T>
class DynamicHashTable {
    List<T>** array;
    int size;
    int numOfElements;
    
    void changeSize(int newSize) {
        List<T>** newArray = new List<T>*[newSize];
        for(int i=0; i<newSize; i++){
            newArray[i] = new List<T>();
        }
        for(int i=0; i<size; i++){
            struct ListNode<T>* curr = array[i]->getFirstNode();
            while(curr){
                newArray[curr->key%(newSize)]->Insert(curr->key, curr->data);
                curr = curr->next;
            }
            delete array[i];
        }
        delete[] array;
        array = newArray;
        size = newSize;
    }
    
    void divideSize(){
        changeSize(size/2);
    }
    
    void multiplySize(){
        changeSize(size*2);
    }
    
public:
    DynamicHashTable(){
        array = new List<T>*[1];
        array[0] = new List<T>();
        size = 1;
        numOfElements = 0;
    }
    
    void Insert(int key, T* data){
        numOfElements+=1;
        if(numOfElements > 5*size){
            multiplySize();
        }
        array[key%size]->Insert(key,data);
    }
    
    void Delete(int key){
        numOfElements -= 1;
        array[key%size]->deleteElement(key);
        if(numOfElements < size/5){
            divideSize();
        }
    }
    
    T* Get(int key){
        return array[key%size]->getElement(key);
    }
    
    ~DynamicHashTable(){
        for(int i=0; i<size; i++){
            delete array[i];
        }
        delete[] array;
    }
};

#endif /* HashTable_h */
