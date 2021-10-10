#include <gtest/gtest.h>

#include "linear_algebra/matrix.hpp"

TEST(UtilTest, Flatten) {
    auto v = linear_algebra::flatten<int>({
        {0, 1, 2, 3},
        {4, 5, 6, 7}
    });

    std::vector <int> correct = {0, 1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(v, correct);
}