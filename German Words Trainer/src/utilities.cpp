#include "utilities.hpp"
#include "exceptions.hpp"

#include <random>
#include <chrono>

template <class T>
T thread_safe_rand(T low, T high) {
    if (!std::is_integral<T>::value) {
        throw DeutschTypeAssertException("Non-int type", "random number generator");
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    std::uniform_int_distribution<T> distribution {low, high};
    return distribution(generator);
}

template float thread_safe_rand<float>(float low, float high) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    std::uniform_real_distribution<float> distribution {low, high};
    return distribution(generator);
}

template double thread_safe_rand<double>(double low, double high) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution {low, high};
    return distribution(generator);
}
