//
//  Cache.hpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/3/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#ifndef Cache_hpp
#define Cache_hpp

#include <stdio.h>
#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>
#include <set>

using namespace std;
class Cache {
public:
    Cache();
    Cache (int c);
    virtual int get(int key) = 0;
    virtual void put(int key, int value) = 0;
    int get_capacity();
    void set_capacity(int c);
private:
    virtual void update(int key, int value) = 0;
    int capacity;
};
#endif /* Cache_hpp */
