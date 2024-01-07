#include "gtest/gtest.h"

// https://algodaily.com/companies/citadel
// https://algodaily.com/challenge_slides/count-the-planes

#include <vector>

int numOfPlanes(std::vector<std::vector<int>> grid)
{
    int count = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        for (int j = 0; j < grid[0].size(); ++j)
        {
            if (grid[i][j] == '.')
                continue;

            bool was_accounted_for_before =
                (i && grid[i - 1][j] == 'P') || (j && grid[i][j - 1] == 'P');
            count += !was_accounted_for_before;
        }
    }
    return count;
}

// print your findings using this function!
#define LOG
void log() { std::cout << numOfPlanes({}); }

// tests

TEST(EmptyGrid, CountThePlanes) { EXPECT_EQ(numOfPlanes({}), 0); }

TEST(VerticalAndHorizontalPlanes, CountThePlanes)
{
    EXPECT_EQ(numOfPlanes({{'.', '.', '.', 'P'},
                           {'.', '.', '.', 'P'},
                           {'P', 'P', '.', 'P'},
                           {'.', '.', '.', 'P'}}),
              2);
}

TEST(Diagonal, CountThePlanes)
{
    EXPECT_EQ(numOfPlanes({{'.', '.', 'P'}, {'.', 'P', '.'}, {'P', '.', '.'}}), 3);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
