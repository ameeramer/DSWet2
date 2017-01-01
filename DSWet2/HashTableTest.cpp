//
//  HashTableTest.cpp
//  DSWet2
//
//  Created by Ameer Amer on 01/01/2017.
//  Copyright © 2017 Ameer Amer. All rights reserved.
//

#include "HashTable.h"
#include "Magizoologist.h"
#include "Reserve.h"
int main(int argc, const char * argv[]) {
    DynamicHashTable<int> hashTable1;
    int* values[10];
    for(int i=0; i<10; i++){
        values[i] = new int;
        *(values[i]) = (i*100)+(i % 7);
    }
    hashTable1.Insert(1,values[1]);
    std::cout << *hashTable1.Get(1) <<std::endl;
    hashTable1.Insert(2,values[2]);
    std::cout << *hashTable1.Get(2) <<std::endl;
    hashTable1.Insert(3,values[3]);
    std::cout << *hashTable1.Get(3) <<std::endl;
    hashTable1.Insert(4,values[4]);
    std::cout << *hashTable1.Get(4) <<std::endl;
    hashTable1.Insert(5,values[5]);
    std::cout << *hashTable1.Get(5) <<std::endl;
    hashTable1.Insert(6,values[6]);
    std::cout << *hashTable1.Get(6) <<std::endl;
    hashTable1.Delete(6);
    std::cout << hashTable1.Get(6) <<std::endl;//should print 0x0 (NULL)
    hashTable1.Delete(5);
    std::cout << hashTable1.Get(5) <<std::endl;//should print 0x0 (NULL)
    hashTable1.Delete(4);
    std::cout << hashTable1.Get(4) <<std::endl;//should print 0x0 (NULL)
    hashTable1.Delete(3);
    std::cout << hashTable1.Get(3) <<std::endl;//should print 0x0 (NULL)
    hashTable1.Delete(2);
    std::cout << hashTable1.Get(2) <<std::endl;//should print 0x0 (NULL)
    hashTable1.Delete(1);
    std::cout << hashTable1.Get(1) <<std::endl;//should print 0x0 (NULL)
    return 0;
}
