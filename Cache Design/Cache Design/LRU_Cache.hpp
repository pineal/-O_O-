//
//  LRU_Cache.hpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/3/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#ifndef LRU_Cache_hpp
#define LRU_Cache_hpp

#include "Cache.hpp"

class LRU_Cache : public Cache {
public:
    LRU_Cache (int c);
    virtual int get(int key);
    virtual void put(int key, int value);
private:
    virtual void update(int key, int value);
    unordered_map<int, list<pair<int, int>>::iterator> _entries;
    list<pair<int, int>> _list;
};
#endif /* LRU_Cache_hpp */
