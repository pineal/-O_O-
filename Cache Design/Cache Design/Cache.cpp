//
//  Cache.cpp
//  Cache Design
//
//  Created by Hesen Zhang on 2/3/17.
//  Copyright © 2017 Hesen Zhang. All rights reserved.
//

#include "Cache.hpp"

Cache::Cache() {
    set_capacity(10);
    cout << "Cache Initialzied" << endl;
};

Cache::Cache(int c) {
    set_capacity(c);
    cout << "Cache Initialzied" << endl;
};

int Cache::get_capacity() {
    return this->capacity;
}

void Cache::set_capacity(int c) {
    if (c <= 0 || c > 100) {
        cout << "Wrong capacity allocated"<<endl;
        exit(1);
    }
    capacity = c;
}
