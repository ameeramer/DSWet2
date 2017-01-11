//
//  AVLTree.h
//  DS-Wet1
//
//  Created by Ameer Amer on 01/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//
#ifndef AVLTree_h
#define AVLTree_h
#include <iostream>
template<class KeyType, class ValueType>
struct AVLTreeNode {
    ValueType* data;
    const KeyType* key;
    struct AVLTreeNode* right;
    struct AVLTreeNode* left;
    struct AVLTreeNode* father;
    const KeyType* rKey;
    const KeyType* lKey;
    int rHeight;
    int lHeight;
};
template<class KeyType, class ValueType,class Compare = std::less<KeyType>, class CompareAge = std::less<KeyType> >
class AVLTree{
    //Properties
    struct AVLTreeNode<KeyType,ValueType>* root;
    int ageCounter;
    //private methods
    void fixYoungestRight(struct AVLTreeNode<KeyType,ValueType>* node)
    {
        node->rKey = max3(node->right->key,node->right->rKey,node->right->lKey);
    }
    void fixYoungestLeft(struct AVLTreeNode<KeyType,ValueType>* node)
    {
        node->lKey = max3(node->left->key,node->left->rKey,node->left->lKey);
    }
    const KeyType* max3(const KeyType* one,const KeyType* two,const KeyType* three)
    {
        const KeyType* temp = CompareAge()(two,one) ? one : two;
        if(CompareAge()(three,temp))
            return temp;
        return three;
    }
    void rollLL(struct AVLTreeNode<KeyType,ValueType>* root) {
        struct AVLTreeNode<KeyType,ValueType>* leftSon = root->left;
        root->lKey = leftSon->rKey;
        leftSon->rKey = max3(leftSon->rKey,root->key,root->rKey);
        leftSon->rHeight = 1 + ((leftSon->rHeight>root->rHeight) ? leftSon->rHeight : root->rHeight);
        root->lHeight=leftSon->rHeight;
        root->left = leftSon->right;
        if(leftSon->right) leftSon->right->father = root;
        leftSon->right = root;
        leftSon->father = root->father;
        struct AVLTreeNode<KeyType,ValueType>* oldFather=root->father;
        root->father = leftSon;
        if(!(root==this->root)){
            if(oldFather->right==root)
                oldFather->right=leftSon;
            else oldFather->left = leftSon;
        }
        else this->root = leftSon;
    }
    void rollRR(struct AVLTreeNode<KeyType,ValueType>* root)
    {
        struct AVLTreeNode<KeyType,ValueType>* temp;
        temp = root->right;
        root->rKey = temp->lKey;
        temp->lKey = max3(temp->lKey,root->key,root->lKey);
        root->rHeight=temp->lHeight;
        temp->lHeight = 1 + ((temp->lHeight>root->lHeight) ? temp->lHeight : root->lHeight);
        root->right = root->right->left;
        if(temp->left) temp->left->father = root;
        temp->left = root;
        temp->father = root->father;
        struct AVLTreeNode<KeyType,ValueType>* oldFather=root->father;
        root->father = temp;
        if(!(root==this->root)){
            if(oldFather->right==root)
                oldFather->right=temp;
            else oldFather->left = temp;
        }
        else this->root = temp;
    }
    void rollRL(struct AVLTreeNode<KeyType,ValueType>* root){
        rollLL(root->right);
        rollRR(root);
    }
    void rollLR(struct AVLTreeNode<KeyType,ValueType>* root){
        rollRR(root->left);
        rollLL(root);
    }
    struct AVLTreeNode<KeyType,ValueType>* AVLFindNode(const KeyType* k)
    {
        return AVLFindNodeAux(k,this->root);
    }

    struct AVLTreeNode<KeyType,ValueType>* AVLFindNodeAux(const KeyType* k,AVLTreeNode<KeyType,ValueType>* root)
    {
        if(Compare()(*(root->key),*k)&&Compare()(*k,*(root->key))) {
            return root;
        }
        if(Compare()(*(root->key),*k))
            if (root->right)
                return AVLFindNodeAux(k,root->right);
        if(Compare()(*k,*(root->key)))
            if (root->left)
                return AVLFindNodeAux(k,root->left);
        return root;
    }
    
    
    const KeyType* getAppropriateAux(const KeyType* k,const AVLTreeNode<KeyType,ValueType>* root)
    {
        if(!root) {
            return NULL;
        }
        if(Compare()(*(root->key), *k)) {
            return getAppropriateAux(k, root->right);
        }
        else {
            return max3(root->key, root->rKey, getAppropriateAux(k, root->left));
        }
    }
    
    void fixHeight(AVLTreeNode<KeyType,ValueType>* root){
        if(!root) return;
        if(root->left)
        {
            root->lHeight = 1 + (root->left->lHeight>root->left->rHeight ? root->left->lHeight : root->left->rHeight);
            fixYoungestLeft(root);
        }
        else{
            root->lHeight = -1;
            root->lKey = NULL;
        }
        if(root->right)
        {
            root->rHeight = 1 + (root->right->lHeight>root->right->rHeight ? root->right->lHeight : root->right->rHeight);
            fixYoungestRight(root);
        }
        else {
            root->rHeight = -1;
            root->rKey = NULL;
        }

    }
    
    void fixTree(struct AVLTreeNode<KeyType,ValueType>* node){
        if(!node)
            return;
        while(node){
            fixHeight(node->right);
            fixHeight(node->left);
            fixHeight(node);
            if((node->lHeight-node->rHeight)==2){
                if(node->left->lHeight-node->left->rHeight>=0){
                    rollLL(node);
                    continue;
                }
                else if(node->left->lHeight-node->left->rHeight==-1)
                    rollLR(node);
            }
            if((node->lHeight-node->rHeight)==-2){
                if(node->right->lHeight-node->right->rHeight==1)
                    rollRL(node);
                else if(node->right->lHeight-node->right->rHeight<=0){
                    rollRR(node);
                continue;
                }
            }
            node=node->father;
        }
        return;
    }
    int sizeAux(AVLTreeNode<KeyType,ValueType>* node){
        if(!node) return 0;
        return 1 + sizeAux(node->left) + sizeAux(node->right);
    }
    int size(){
        return sizeAux(this->root);
    }
    void treeToArrays(const KeyType** a,ValueType** b){
        treeToArraysAux(a, b, this->root);
    }

    void treeToArraysAux(const KeyType** a,ValueType** b, struct AVLTreeNode<KeyType,ValueType>* node){
        static int i = -1;
        if(!node) return;
        treeToArraysAux(a, b, (node->left));
        i++;
        a[i] = node->key;
        b[i] = node->data;
        treeToArraysAux(a, b, (node->right));
        if(i != -1 && node == this-> root){
            i=-1;
        }
    }
public:
    AVLTree(){
        root = NULL;
        ageCounter=0;
    }
    AVLTree(struct AVLTreeNode<KeyType,ValueType>* root){
        this->root = root;
    }
    ValueType* Find(const KeyType* k)
    {
        return this->FindAux(k,this->root);
    }
    ValueType* FindAux(const KeyType* k,AVLTreeNode<KeyType,ValueType>* root)
    {
        if(!root||!k)
            return NULL;
        if(Compare()(*(root->key),*k)&&Compare()(*k,*(root->key))) {
            return root->data;
        }
        if(Compare()(*(root->key),*k))
            if (root->right){
                return FindAux(k, root->right);
            }
        if(Compare()(*k,*(root->key)))
            if (root->left){
                return FindAux(k, root->left);
            }
        return NULL;
    }

    bool Insert(ValueType* data,const KeyType* key)
    {
        struct AVLTreeNode<KeyType,ValueType>* toAdd = new struct AVLTreeNode<KeyType,ValueType>;
        toAdd->data = data;
        toAdd->key= key;
        toAdd->right=NULL;
        toAdd->left=NULL;
        toAdd->father = NULL;
        toAdd->rHeight=-1;
        toAdd->lHeight=-1;
        toAdd->rKey = NULL;
        toAdd->lKey=NULL;
        if(!root){
            root = toAdd;
            return true;;
        }
        struct AVLTreeNode<KeyType,ValueType>* root2 = AVLFindNode(key);
        if(Compare()(*(root2->key),*key)&&Compare()(*key,*(root2->key))) {
            delete toAdd;
            return false;
        }
        toAdd->father = root2;
        if(Compare()(*(root2->key),*key)) {
            root2->right = toAdd;
            root2->rHeight=0;
            root2->rKey = key;
        }
        else{
            root2->lHeight=0;
            root2->left=toAdd;
            root2->lKey= key;
        }
        fixTree(toAdd);
        return true;
    }
    

    void Delete(const KeyType* k){
        struct AVLTreeNode<KeyType,ValueType>* nodeToDelete = AVLFindNode(k);
        struct AVLTreeNode<KeyType,ValueType>* father = nodeToDelete->father;
        bool temp1=false;
        
        if(!Compare()(*(nodeToDelete->key),*k)&&!Compare()(*k,*(nodeToDelete->key))){
            return;
        }

        //the node is a leaf
        else if(!nodeToDelete->left && !nodeToDelete->right){
            if(father){
                if(father->left==nodeToDelete){
                    father->left = NULL;
                    father->lHeight = -1;
                    delete father->lKey;
                    father->lKey = NULL;
                } else {
                    father->right = NULL;
                    father->rHeight=-1;
                    delete father->rKey;
                    father->rKey = NULL;
                }
            }
            if(nodeToDelete == this->root){
                this->root = NULL;
                temp1=true;
            }
            fixTree(father);
            delete nodeToDelete;
        }
        //the node has only a left son
        else if(nodeToDelete->left && !nodeToDelete->right){
            if(father)
            {
                 father->left==nodeToDelete ? father->left = nodeToDelete->left : father->right = nodeToDelete->left;
                
            }

            nodeToDelete->left->father = father;
            if(nodeToDelete == this->root){
                temp1=true;
                this->root = nodeToDelete->left;
            }
            delete nodeToDelete;
            fixTree(father);
        }
        //the node has only a right son
        else if(!nodeToDelete->left && nodeToDelete->right){
          //  std::cout << "1" << std::endl;
            if(father)
                father->left==nodeToDelete ? father->left = nodeToDelete->right : father->right = nodeToDelete->right;
            nodeToDelete->right->father = father;
            if(nodeToDelete == this->root){
                temp1=true;
                this->root = nodeToDelete->right;
            }
            delete nodeToDelete;
            fixTree(father);
        }//the node to delete has two sons
        else {
            struct AVLTreeNode<KeyType,ValueType>* currNode;
            for (currNode = nodeToDelete->right; currNode->left!=NULL; currNode=currNode->left) {
                continue;
            }
            ValueType* tempValue = currNode->data;
            const KeyType* tempKey = currNode->key;
            currNode->data = nodeToDelete->data;
            currNode->key = nodeToDelete->key;
            nodeToDelete->data = tempValue;
            nodeToDelete->key = tempKey;
            father = currNode->father;
            //the node is a leaf
            if(!currNode->left && !currNode->right){
                if(father)
                    father->left==currNode ? father->left = NULL : father->right = NULL;
                if(currNode == this->root){
                    this->root = NULL;
                    temp1=true;
                }
                delete currNode;
            }
            //the node has only a right son
            else{
                if(father)
                    father->left==currNode ? father->left = currNode->right : father->right = currNode->right;
                currNode->right->father = father;
                if(currNode == this->root){
                    this->root = nodeToDelete->left;
                    temp1=true;
                }
                delete currNode;
            }
            fixTree(father);
        }
    }
    
    ValueType* getAppropriate(KeyType* k)
    {
        if(!(this->root))
            return NULL;
        const KeyType* mag = getAppropriateAux(k,this->root);
        return Find(mag);
    }
    //TODO: remove this
    void treeToArrayByKeys(const KeyType** a){
        treeToArrayByKeysAux(a, this->root);
    }

    void treeToArrayByKeysAux(const KeyType** a, AVLTreeNode<KeyType,ValueType>* node){
        static int i = -1;
        if(!node) return;
        treeToArrayByKeysAux(a, node->right);
        i++;
        a[i] = node->key;
        treeToArrayByKeysAux(a, node->left);
        if(node == this->root && i!=-1) i=-1;
    }
    ~AVLTree(){
        deleteTreeNodesAux(this->root);
    }
    void deleteTreeNodesAux(AVLTreeNode<KeyType, ValueType>* tr){
        if(!tr){
            return;
        }
        deleteTreeNodesAux(tr->right);
        deleteTreeNodesAux(tr->left);
        delete tr;
    }

    template<class Func>
    void map(Func f){
        mapAux(f,this->root);
    }

    template<class Func>
    void mapAux(Func f, AVLTreeNode<KeyType,ValueType>* node){
        if(!node) return;
        mapAux(f,node->left);
        f(node->data);
        mapAux(f,node->right);
    }

    ValueType* getMax(){
        return getMaxAux(this->root);
    }
    ValueType* getMaxAux(AVLTreeNode<KeyType,ValueType>* node){
        if(!node) return NULL;
        if(!node->right) return node->data;
        return getMaxAux(node->right);
    }

    void removeAllData(){
        removeAllDataAux(this->root);
    }
    void removeAllDataAux(AVLTreeNode<KeyType,ValueType>* node){
        if(!node) return;
        removeAllDataAux(node->left);
        delete node->key;
        delete node->data;
        removeAllDataAux(node->right);
    }
    void removeAllKeys(){
        removeAllKeysAux(this->root);
    }
    void removeAllKeysAux(AVLTreeNode<KeyType,ValueType>* node){
        if(!node) return;
        removeAllKeysAux(node->left);
        delete node->key;
        removeAllKeysAux(node->right);
    }


};


#endif /* AVLTree_h */
