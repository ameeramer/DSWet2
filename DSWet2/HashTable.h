//
//  HashTable.h
//  DSWet2
//
//  Created by Ameer Amer on 31/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

template <class T>
struct ListNode {
    int key;
    T* data;
    struct ListNode* next;
};

template <class T>
class List {
    struct ListNode* head;
    
public:
    List(){
        head = new struct ListNode;
        head->key = -1;
        head->data = null;
        head->next = null;
    }
    
    void Insert(int key, T* data){
        struct ListNode* newNode = new struct ListNode;
        newNode->key = key;
        newNode->data = data;
        newNode->next = head->next;
        head->next = newNode;
    }
    
    void deleteElement(int key){
        struct ListNode* curr = head->next;
        while(curr->next){
            if(curr->next->key = key){
                struct ListNode* toDelete = curr->next;
                curr->next = toDelte->next;
                delete (toDelete);
            }
            curr = curr->next;
        }
    }
    
    T* getElement(int key){
        struct ListNode* curr = head->next;
        while(curr){
            if(curr->key = key){
                return curr->data;
            }
            curr = curr->next;
        }
        return null;
    }
    
    struct ListNode* getFirstNode(){
        return head->next;
    }
    
    ~List(){
        struct ListNode* curr = head;
        struct ListNode* toDelete;
        while(curr){
            toDelete = curr;
            curr = curr->next;
            delete(toDelete);
        }
    }
};

template <class T>
class DynamicHashTable {
    List** array;
    int size;
    int numOfElements;
    
    static void changeSize(int newSize) {
        List** newArray = new List*[newSize];
        for(int i=0; i<newSize; i++){
            newArray[i] = new List();
        }
        for(int i=0; i<size; i++){
            struct ListNode* curr = array[i]->getFirstNode();
            while(curr){
                newArray[curr->key%(newSize)]->insert(curr->key, curr->data);
            }
            delete array[i];
        }
        delete[] array;
        array = newArray;
        size = newSize;
    }
    
    static void divideSize(){
        changeSize(size/2);
    }
    
    static void multiplySize(){
        changeSize(size*2);
    }
    
public:
    DynamicHashTable(){
        array = new List*[1];
        array[1] = new List();
        size = 1;
        numOfElements = 0;
    }
    
    void Insert(int key, T* data){
        numOfElements+=1;
        if(numOfElements > 5*size){
            multiplySize();
        }
        array[key%size]->insert(key,data);
    }
    
    void Delete(int key){
        numOfElemets -= 1;
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
