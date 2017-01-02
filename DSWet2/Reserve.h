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
class Reserve{
    DynamicHashTable<Magizoologist> magis;
    UnionFind creatures;
    int levels[];
    //TODO: add ranked tree property for magis.
    
public:
    Reserve(int n, int levels1[]) : creatures(n,levels1){
        for(int i=0; i<n; i++){
            levels[i] = levels1[i];
        }
    }
    //TODO: add inserting to the ranked tree.
    void AddMagizoologist(int magiID, int magiLvl){
        Magizoologist* magiToAdd = new Magizoologist(magiID, magiLvl);
        magis.Insert(magiID, magiToAdd);
    }
    //TODO: add deleting from the ranked tree.
    void RemoveMagizoologist(int magiID){
        magis.Delete(magiID);
    }
    
    void RemoveBarrier(int creature1, int creature2){
        creatures.Union(creature1, creature2);
    }
    
    //TODO: add updating the ranked tree.
    void releaseMagizoologist(int magiID){
        magis.Get(magiID)->release();
    }
    
    int getCreatureOfMagi(int magiID){
        return magis.Get(magiID)->getCreature();
    }
    bool areCreatureInSameArea(int creature1, int creature2){
        return creatures.find(creature1) == creatures.find(creature2);
    }
    int getSizeOfArea(int creatureID){
        return creatures.sizeOfSet(creatureID);
    }
    
    //TODO: add the assignCreatureToMagi method.
};

#endif /* Reserve_h */
