#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>

template <typename T>
T getRand (const T & min, const T & max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    std::uniform_int_distribution<T> distribution(min,max);
    return distribution(generator);
}

template <typename T = double>
double getRand (const double & min, const double & max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<double> unif(min,max);
    static std::default_random_engine re(seed);
    return unif(re);
} 

template <typename T = float>
float getRand (const float & min, const float & max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::uniform_real_distribution<float> unif(min,max);
    static std::default_random_engine re(seed);
    return unif(re);
}

#endif 