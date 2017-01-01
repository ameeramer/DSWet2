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
};

template <class T>
class DynamicHashTable {
    List* array;
    int size;
    
    static void multiplySize {
        List newList;
        for(int i=0; i<size; i++){
            
        }
    }
};

#endif /* HashTable_h */
