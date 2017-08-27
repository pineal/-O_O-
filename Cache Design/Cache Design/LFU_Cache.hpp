//
//  LFU_Cache.hpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/4/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#ifndef LFU_Cache_hpp
#define LFU_Cache_hpp

#include "Cache.hpp"



class LFU_Cache : public Cache {
public:
    struct Node {
        int key;
        int val;
        int f;
        Node(int k, int v) : f(1), key(k), val(v) {}
         Node(int k, int v, int fre) : key(k), val(v), f(fre) {}
    };
    struct Cmp {
        bool operator() (const Node & a, const Node & b) {
            return a.f < b.f;
        }
    };
    LFU_Cache (int c);
    virtual int get(int key);
    virtual void put(int key, int value);
private:
    virtual void update(int key, int value);
    unordered_map<int, multiset<Node, Cmp>::iterator> _entries;
    multiset<Node, Cmp> _list;
};
#endif /* LFU_Cache_hpp */
