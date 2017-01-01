//
//  UnionTest.cpp
//  DSWet2
//
//  Created by Ameer Amer on 31/12/2016.
//  Copyright © 2016 Ameer Amer. All rights reserved.
//

#include "Union.h"

int main(int argc, const char * argv[]) {
    int values[10];
    for(int i=0; i<10; i++){
        values[i] = (i*100)+(i % 7);
    }
    UnionFind unionFind1(10, values);
    unionFind1.Union(1, 2);
    std::cout << unionFind1.find(2) << std::endl;
    std::cout << unionFind1.find(1) << std::endl;
    std::cout << unionFind1.find(3) << std::endl;
    unionFind1.Union(3,4);
    unionFind1.Union(3,5);
    std::cout << unionFind1.find(3) << std::endl;
    std::cout << unionFind1.find(4) << std::endl;
    std::cout << unionFind1.find(5) << std::endl;
    unionFind1.Union(5,1);
    std::cout << unionFind1.find(1) << std::endl;
    std::cout << unionFind1.find(2) << std::endl;
    std::cout << unionFind1.find(3) << std::endl;
    std::cout << unionFind1.find(4) << std::endl;
    std::cout << unionFind1.find(5) << std::endl;
    unionFind1.Union(1,5);
    std::cout << unionFind1.dataOfSet(1) << std::endl;
    return 0;
}
