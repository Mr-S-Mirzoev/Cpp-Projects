#include "quantity_by_sum.hpp"

#include "digit.hpp"
#include "permutations.hpp"

#include <iostream>

inline static int64_t quantity_of_numbers_with_sum_worker(short sum, short length, const std::string &s) {
    Digit lowest = (s.length()) ? s[0] : '0';
    int64_t overall = 0;

    if (length > 1) {
        Digit upper_bound{short(sum / length)};
        for (Digit i = lowest; i <= upper_bound; ++i) {
            overall += quantity_of_numbers_with_sum_worker(sum - i.to_dec(), length - 1, s + i.to_char());
        }

        return overall;
    } else {
        if (sum < 13 && sum >= 0) {
            Digit last{sum};

            return permutations_on_set(s + last.to_char());
        } else {
            return 0;
        }
    }
}

int64_t quantity_of_numbers_with_sum(short sum) {
    return quantity_of_numbers_with_sum_worker(sum, 6, "");
}