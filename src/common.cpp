//
// Created by VokamisAir on 1/9/21.
//

#include "common.h"

int randomInteger(int to, int from){
    std::random_device randomizerSeed;
    std::default_random_engine randomEngine(randomizerSeed());
    std::uniform_int_distribution<int> randomRange(from, to);
    return randomRange(randomEngine);
}