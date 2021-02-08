#include "factorial.hpp"

#include <vector>

constexpr int CACHE_INITIAL_SIZE = 10;

static std::vector<int> fact_cache(CACHE_INITIAL_SIZE);
static int max_available = 0;

static inline int factorial_worker(int k) {
    if (max_available == 0) {
        fact_cache[0] = 1;
    }
    
    int result = fact_cache[max_available];

    for (int i = max_available + 1; i <= k; ++i) {
        result *= i;
        fact_cache[i] = result;
    }

    return result;
} 

int factorial(int k) { // int is enough since k <= 6.
    
    if (k + 1 > fact_cache.size()) { // general-case check
        fact_cache.resize(k + 1);
    }

    int result = fact_cache[k];

    if (result == 0) { // cache miss
        result = factorial_worker(k);
    }

    return result;
}