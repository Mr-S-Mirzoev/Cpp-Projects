#include "permutations.hpp"

#include <gtest/gtest.h>
#include <string>

TEST(PermutationsTest, OneType) {
    ASSERT_EQ(1, permutations_on_set("000"));
}

TEST(PermutationsTest, ManyTypes) {
    ASSERT_EQ(3, permutations_on_set("001"));
    ASSERT_EQ(6, permutations_on_set("012"));
    ASSERT_EQ(12, permutations_on_set("0012"));
    ASSERT_EQ(60, permutations_on_set("011222"));
}
