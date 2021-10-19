#include "factorial.hpp"

#include <gtest/gtest.h>

TEST(FactorialTest, Zero) {
    ASSERT_EQ(1, factorial(0));
}

TEST(FactorialTest, Positive) {
    ASSERT_EQ(1, factorial(1));
    ASSERT_EQ(2, factorial(2));
    ASSERT_EQ(6, factorial(3));
    ASSERT_EQ(720, factorial(6));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
