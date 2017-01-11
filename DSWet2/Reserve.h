//
//  Reserve.h
//  DSWet2
//
//  Created by Ameer Amer on 01/01/2017.
//  Copyright © 2017 Ameer Amer. All rights reserved.
//

#ifndef Reserve_h
#define Reserve_h
#include "HashTable.h"
#include "Union.h"
#include "Magizoologist.h"
#include "AVLTree.h"
#include "library2.h"
#include <iostream>

class CompareInts {
public:
    bool operator()(int a, int b){
        return a <= b;
    }
};

class Reserve{
    DynamicHashTable<Magizoologist> magis;
    UnionFind creatures;
    int* levels;
    //TODO: add ranked tree property for magis.DONE
    AVLTree<lvlMg,Magizoologist,CompareMG,CompareAges> magisTree;

public:
    Reserve(int n, int levels1[]) : creatures(n,levels1){
        levels = new int[n];
        for(int i=0; i<n; i++){
            levels[i] = levels1[i];
        }
    }
    //TODO: add inserting to the ranked tree.DONE
    StatusType addMagizoologist(int magiID, int magiLvl){
        Magizoologist* magiToAdd;
        Magizoologist* magiToAdd2;
        static int ageCounter = 0;
        try{
        magiToAdd = new Magizoologist(magiID, magiLvl,ageCounter);
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        try{
        magiToAdd2 = new Magizoologist(magiID, magiLvl,ageCounter);
        }
        catch(std::bad_alloc& e)
        {
            delete magiToAdd;
            return ALLOCATION_ERROR;
        }
        if(magis.Get(magiID)!=NULL)
            return FAILURE;
        magis.Insert(magiID, magiToAdd);
        lvlMg* lvl = new lvlMg(magiID,magiLvl,ageCounter++);
        if(!lvl) return ALLOCATION_ERROR;
        magisTree.Insert(magiToAdd,lvl);
        return SUCCESS;
    }
    //TODO: add deleting from the ranked tree.DONE
    StatusType removeMagizoologist(int magiID){
        Magizoologist* mag = magis.Get(magiID);
        if(mag==NULL)
            return FAILURE;
        lvlMg* temp = new lvlMg(magiID,mag->getLvl(),mag->getAge());
        if(!temp) return ALLOCATION_ERROR;
        releaseMagizoologist(magiID);
        magisTree.Delete(temp);
        magis.Delete(magiID);
        delete temp;
        return SUCCESS;
    }

    StatusType removeBarrier(int creature1, int creature2){
        bool check;
        areCreatureInSameArea(creature1,creature2,&check);
        if(check == true||creature1 >= creatures.totalSize()||creature2>=creatures.totalSize())
            return FAILURE;
        creatures.Union(creature1, creature2);
        return SUCCESS;
    }

    //TODO: add updating the ranked tree.DONE
    StatusType releaseMagizoologist(int magiID){
        Magizoologist* mag = magis.Get(magiID);
        if(!mag)
            return FAILURE;
        if(mag->getCreature()==-1) return FAILURE;
        mag->release();
        magisTree.Insert(mag,mag->getThis());
        return SUCCESS;
    }

    StatusType getCreatureOfMagi(int magiID, int* creatureID){
        if(!creatureID) return INVALID_INPUT;
        Magizoologist* mag = magis.Get(magiID);
        if(!mag) return FAILURE;
        *creatureID = mag->getCreature();
        if(*creatureID == -1) return FAILURE;
        return SUCCESS;
    }
    StatusType areCreatureInSameArea(int creature1, int creature2,  bool* sameArea){
        if(!sameArea||creature1 >= creatures.totalSize()||creature2>=creatures.totalSize()) return INVALID_INPUT;
        *sameArea = creatures.find(creature1) == creatures.find(creature2);
        return SUCCESS;
    }
    StatusType getSizeOfArea(int creatureID, int* sizeOfArea){
        if(creatureID>=creatures.totalSize()) return INVALID_INPUT;
        *sizeOfArea = creatures.sizeOfSet(creatureID);
        return SUCCESS;
    }
    StatusType assignMagizoologistToCreature(int CreatureID)
    {
        Magizoologist* refresh;
        lvlMg* temp;
        // Check if creature is in the range of set
        if(CreatureID>=creatures.totalSize()) return FAILURE;
        int lvl = creatures.dataOfSet(CreatureID);
        try{
            temp = new lvlMg(-1,lvl,0);
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        if(!temp) return ALLOCATION_ERROR;
        Magizoologist* mag = (magisTree.getAppropriate(temp));
        //if no appropriate magis were found
        if(!mag) return FAILURE;
        magis.Delete(mag->getID());
        mag->assignCreature(CreatureID);
        try{
            refresh = new Magizoologist(mag->getID(), mag->getLvl(),mag->getAge());
        }
        catch(std::bad_alloc& e)
        {
            return ALLOCATION_ERROR;
        }
        refresh->assignCreature(CreatureID);
        magis.Insert(mag->getID(),refresh);
        magisTree.Delete(mag->getThis());
        return SUCCESS;
    }
};

#endif /* Reserve_h */
