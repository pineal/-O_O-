//
//  main.cpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/3/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#include "LRU_Cache.hpp"
#include "LFU_Cache.hpp"
int main(int argc, const char * argv[]) {
    Cache *lru = new LRU_Cache(2);
    lru->put(1, 1);
    lru->put(2, 2);
    lru->get(1);
    lru->put(3, 3);
    lru->get(2);
    lru->put(3, 5);
    lru->get(3);
    lru->get(1);
    
    
    Cache *lfu = new LFU_Cache(2);
    lfu->put(1, 1);
    lfu->put(2, 2);
    lfu->get(1);
    lfu->put(3, 3);
    lfu->get(2);
    lfu->put(3, 5);
    lfu->get(3);
    lfu->get(1);
    
    return 0;
}
