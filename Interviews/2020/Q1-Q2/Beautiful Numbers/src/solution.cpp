#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "quantity_by_sum.hpp"

int main()
{
    std::cout << "Quantity of \"beautiful\" 13-digit numbers in 13-digit system of calculations:"
              << std::endl;

    unsigned long long result_for_all_sums = 0;

    for (short sum = 0; sum <= 12 * 6; ++sum)
    {
        result_for_all_sums += std::pow(quantity_of_numbers_with_sum(sum), 2);
    }

    unsigned long long result = result_for_all_sums * 13;

    std::cout << std::scientific;
    std::cout << "In scientific notation: " << result << std::endl;
    std::cout << std::fixed;
    std::cout << "In usual notation: " << result << std::endl;
}
