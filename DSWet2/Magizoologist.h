//
//  Magizoologist.h
//  DSWet2
//
//  Created by Ameer Amer on 01/01/2017.
//  Copyright © 2017 Ameer Amer. All rights reserved.
//

#ifndef Magizoologist_h
#define Magizoologist_h
struct lvlMg{
    const int mgID;
    int mgLvl;
    int mgAge;
    lvlMg(const int ID, int mgLvl,int age): mgID(ID){
        this->mgLvl = mgLvl;
        this->mgAge = age;
    }
};
class CompareMG{
public:
    bool operator()(lvlMg a, lvlMg b){
        //return a.mgLvl<=b.mgLvl;

        return a.mgLvl==b.mgLvl ? a.mgID<=b.mgID : a.mgLvl<=b.mgLvl;

    }
};
class CompareAges{
public:
    bool operator()(const lvlMg* a,const lvlMg* b){
        //return a.mgLvl<=b.mgLvl;
        if(a==NULL) return true;
        if(b==NULL) return false;
        return a->mgAge<b->mgAge;
        
    }
};
class Magizoologist{
    const int magiID;
    const int magiLvl;
    int assignedCreatureID;
    lvlMg* thisMg;
    int age;

public:
    Magizoologist(int magiID, int magiLvl,int age2): magiID(magiID), magiLvl(magiLvl){
        assignedCreatureID = -1;
        try{
            thisMg = new lvlMg(magiID,magiLvl,age2);
        }catch(std::bad_alloc& e){
            throw e;
        }
        age=age2;
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
    int getID()
    {
        return magiID;
    }
    int getLvl()
    {
        return magiLvl;
    }
    lvlMg* getThis()
    {
        return thisMg;
    }
    int getAge(){
        return this->age;
    }
};

#endif /* Magizoologist_h */
