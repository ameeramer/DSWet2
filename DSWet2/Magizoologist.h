//
//  Magizoologist.h
//  DSWet2
//
//  Created by Ameer Amer on 01/01/2017.
//  Copyright © 2017 Ameer Amer. All rights reserved.
//

#ifndef Magizoologist_h
#define Magizoologist_h

class Magizoologist{
    const int magiID;
    const int magiLvl;
    int assignedCreatureID;
    
public:
    Magizoologist(int magiID, int magiLvl): magiID(magiID), magiLvl(magiLvl){
        assignedCreatureID = -1;
    }
    
    void assignCreature(int crID){
        assignedCreatureID = crID;
    }
    
    void release(){
        assignedCreatureID = -1;
    }
    
    int getCreature(){
        return assignedCreatureID;
    }
};

#endif /* Magizoologist_h */
