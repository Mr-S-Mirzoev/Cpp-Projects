#ifndef MY_RANDOM_H
#define MY_RANDOM_H

#include <random>

template <typename T>
T getRand (const T & min, const T & max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    std::uniform_int_distribution<T> distribution(min,max);
    return distribution(generator);
}

#endif