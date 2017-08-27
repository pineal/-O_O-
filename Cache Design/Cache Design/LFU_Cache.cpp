//
//  LFU_Cache.cpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/4/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#include "LFU_Cache.hpp"

LFU_Cache::LFU_Cache (int c) {
    set_capacity(c);
    cout<<"LFU Cache Initialized"<<endl;
}

int LFU_Cache::get(int key) {
    auto it = _entries.find(key);
    if (it == _entries.end()) {
        return -1;
    }
    auto del = it->second;
    _list.erase(del);
    _entries[key] = _list.emplace(del->key, del->val, del->f + 1);
    return del->val;
}

void LFU_Cache::put(int key, int value) {
    auto it = _entries.find(key);
    if (it == _entries.end()) {
        if (_entries.size() == get_capacity()) {
            _entries.erase(_list.begin()->key);
            _list.erase(_list.begin());
        }
        Node tmp(key, value);
        _list.insert(tmp);
    } else {
        auto del = it->second;
        _list.erase(del);
        _entries[key] = _list.emplace(value, del->key, del->f + 1);
    }
}

void LFU_Cache::update(int key, int value) {
    
}
