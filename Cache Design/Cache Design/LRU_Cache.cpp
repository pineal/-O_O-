//
//  LRU_Cache.cpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/3/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#include "LRU_Cache.hpp"

LRU_Cache::LRU_Cache(int c) {
    set_capacity(c);
    cout << "LRU Cache Initialzied" << endl;
};

int LRU_Cache ::get(int key) {
    if (_entries.find(key) == _entries.end()) {
        cout << "Error: key not found" << endl;
        return -1;
    } else {
        int v = _entries[key]->second;
        update(key, v);
        return v;
    }
};

void LRU_Cache::put(int key, int value) {
    if (_list.size() == get_capacity() && _entries.find(key) == _entries.end()) {
        auto p = _list.back();
        _list.pop_back();
        _entries.erase(p.first);
    }
    this->update(key, value);
};

void LRU_Cache::update(int key, int value) {
    //try to find the <key,iterator> entry found entries
    auto it = _entries.find(key);
    //if entry found
    if (it != _entries.end()) {
        //delete the current node in list
        _list.erase(it->second);
    }
    //update the position to the front of the list
    _list.emplace_front(key, value);
    //remap the entry
    _entries[key] = _list.begin();
}


