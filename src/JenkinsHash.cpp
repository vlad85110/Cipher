//
// Created by vlad on 25.11.23.
//

#include "JenkinsHash.h"

uint32_t JenkinsHash::calculate(const String &key) {
    uint32_t hash = 0;

    for (size_t i = 0; i < key.length(); ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}
