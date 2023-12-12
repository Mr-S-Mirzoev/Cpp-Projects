#include <cmath>
#include <gtest/gtest.h>

#include "linear_algebra/matrix.hpp"

TEST(MatrixPowerTest, ZeroDeterminant)
{
    linear_algebra::Matrix a(3, 3);
    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            a[{i, j}] = (i + 1) * (j + 2) % 9;

    EXPECT_THROW(a ^ (-1), linear_algebra::ZeroDeterminantException);
}

TEST(MatrixPowerTest, Inverse)
{
    linear_algebra::Matrix a(3, 3);
    for (std::size_t i = 0; i < 3; ++i)
        for (std::size_t j = 0; j < 3; ++j)
            a[{i, j}] = std::pow((i + 1), (j + 2));

    linear_algebra::Matrix correct_result(
        {{3., -.75, 0.111}, {-2.5, 1., -0.167}, {.5, -.25, .056}});

    EXPECT_EQ(a ^ (-1), correct_result);
}

TEST(MatrixPowerTest, SimpleSqr)
{
    linear_algebra::Matrix a = linear_algebra::eye(3, 3);

    EXPECT_EQ(a ^ 2, linear_algebra::eye(3, 9));
}

TEST(MatrixPowerTest, Sqr)
{
    linear_algebra::Matrix a({{0, 3, 4}, {7, 9, 2}, {8, 9, 9}});

    linear_algebra::Matrix correct_result({{53, 63, 42}, {79, 120, 64}, {135, 186, 131}});

    EXPECT_EQ(a ^ 2, correct_result);
}