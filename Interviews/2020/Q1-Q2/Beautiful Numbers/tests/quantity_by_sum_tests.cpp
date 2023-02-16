#include "quantity_by_sum.hpp"

#include <gtest/gtest.h>

TEST(QuantityTest, Length0) {
    ASSERT_EQ(1, quantity_of_numbers_with_sum(0));
}

TEST(QuantityTest, Length1) {
    ASSERT_EQ(6, quantity_of_numbers_with_sum(1));
}

TEST(QuantityTest, Length2) {
    ASSERT_EQ(21, quantity_of_numbers_with_sum(2));
}