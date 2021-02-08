#include "permutations.hpp"
#include "factorial.hpp"

#include <iostream>
#include <vector>

inline static std::vector<int> elements_by_count(const std::string &numbers) {
    std::vector<int> count;
    int current = 1;

    for (int i = 1; i < numbers.size(); ++i) {
        if (numbers[i] != numbers[i - 1]) {
            count.push_back(current);
            current = 1;
        } else {
            ++current;
        }
    }

    count.push_back(current);

    return count;
}

int permutations_on_set(const std::string &numbers) {
    std::vector<int> count = elements_by_count(numbers);

    int result = factorial(numbers.size());

    for (int val : count) {
        result /= factorial(val);
    }

    return result;
}