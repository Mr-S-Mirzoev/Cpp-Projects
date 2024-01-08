#include "manhattan.h"

#include <gtest/gtest.h>

TEST(ManhattanTest, HandlesSimpleCase)
{
    /*
    #####################
    # - # - # A # - # A #
    #####################
    # - # A # - # - # - #
    #####################
    # - # - # - # B # - #
    #####################
    # A # - # - # - # - #
    #####################
    # - # A # - # A # A #
    #####################
    */
    // clang-format off
    std::vector<std::string_view> field = {
        "CxAxA",
        "xAxxx",
        "xxxBx",
        "Axxxx",
        "xACAA"
    };
    // clang-format on

    ManhattanProcessor processor(field);

    EXPECT_EQ(processor.process('A', 'B'), 2);
    EXPECT_EQ(processor.process('C', 'B'), 3);
}