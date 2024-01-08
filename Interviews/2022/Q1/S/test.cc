#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include "optimal_root.h"
#include "tree_path.h"

TEST(TreeOptimalRootTest, HandlesSimpleTree)
{
    const int nodes_count = 4;
    /*
    - Original tree:
            0
            1
        2       3

    - Optimal tree:
            1
        0   2   3
    */
    const Edges edges = {{1, 0}, {1, 2}, {1, 3}};

    const int optimal_root = find_optimal_root(edges, nodes_count);
    EXPECT_EQ(optimal_root, 1);
}

TEST(TreeOptimalRootTest, HandlesComplexTree)
{
    const int nodes_count = 8;
    /*
         0
       1    2
     3     4  5
       6
      7

    */
    const Edges edges = {{0, 1}, {0, 2}, {1, 3}, {3, 6}, {6, 7}, {2, 4}, {2, 5}};

    const int optimal_root = find_optimal_root(edges, nodes_count);
    EXPECT_EQ(optimal_root, 1);
}

TEST(TreeOptimalRootTest, HandlesLinearTree)
{
    const int nodes_count = 3;
    /*
    - Original tree:
            0
      1
         2
    - Optimised tree:
            1
        0       2
    */
    const Edges edges = {{0, 1}, {1, 2}};

    const int optimal_root = find_optimal_root(edges, nodes_count);
    EXPECT_EQ(optimal_root, 1);
}

TEST(TreeOptimalRootTest, HandlesSingleElementTree)
{
    const int nodes_count = 1;
    const Edges edges = {};

    const int optimal_root = find_optimal_root(edges, nodes_count);
    EXPECT_EQ(optimal_root, 0);
}

TEST(TreeOptimalRootTest, GetTallestPathSimpleTree)
{
    const int nodes_count = 4;
    /*
    - Original tree:
            0
            1
        2       3
    */
    const Edges edges = {{1, 0}, {1, 2}, {1, 3}};

    TreePath expected_path = {2, 1, 0}; // Assuming the path starts from the leaf and goes up
    TreePathUtils utils(edges, nodes_count);
    EXPECT_EQ(utils.get_tallest_path(0), expected_path);
}

TEST(TreeOptimalRootTest, GetDiameterPathComplexTree)
{
    const int nodes_count = 8;
    /*
    - Original tree:
         0
       1    2
     3     4  5
       6
      7
    */
    const Edges edges = {{0, 1}, {0, 2}, {1, 3}, {3, 6}, {6, 7}, {2, 4}, {2, 5}};

    TreePath expected_path = {7, 6, 3, 1, 0, 2, 4}; // One of the longest paths
    TreePathUtils utils(edges, nodes_count);
    EXPECT_EQ(utils.get_diameter_path(0), expected_path);

    // The diameter path should be simmetric
    std::reverse(expected_path.begin(), expected_path.end());
    /*
    - The tree viewed from the 7 node perspective:
          7
        6
          3  4  5
         1    2
           0
    */
    EXPECT_EQ(utils.get_diameter_path(7), expected_path);
}
