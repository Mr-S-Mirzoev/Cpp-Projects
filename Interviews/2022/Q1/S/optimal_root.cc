// Input: A tree of n nodes .. (integer n, adjacency list of edges)
// Output: Nodes that minimize the tree height if used as roots

/*
Example:
   0
   |
   1
  / \
 2   3
*/

// Input: n = 4, edges = [[1,0],[1,2],[1,3]]
// Output: 1

/*
     0
   1    2
 3     4  5
   6
  7

// Input: n = 8, edges = [[0,1],[0,2],[1,3],[3,6],[6,7],[2,4],[2,5]]
// Output: 1

*/
#include <iostream>
#include <vector>

using Tree = std::vector<std::vector<int>>;
using Path = std::vector<int>;

Path get_tallest_path(int curr, Tree const& v, int prev = -1)
{
    /**
     * @brief Get tallest path from root to leaf
     */
    int next;
    Path current_path;

    for (int succ : v[curr])
    {
        if (prev != -1 && succ == prev)
            continue;

        auto tallest_path = get_tallest_path(succ, v, curr);
        if (tallest_path.size() > current_path.size())
        {
            next = succ;
            current_path = std::move(tallest_path);
        }
    }

    current_path.push_back(curr);
    return current_path;
}

Path get_diameter_path(int curr, Tree const& v, int prev = -1)
{
    /**
     * @brief Get tallest path from node to node
     */

    // base case where tree is empty
    if (v[curr].size() == 1)
        return {curr};

    Path tallest_path;
    Path second_tallest_path;
    Path longest_dia_path;

    for (int succ : v[curr])
    {
        if (prev != -1 && succ == prev)
            continue;

        auto vertical_path = get_tallest_path(succ, v, curr);
        auto diagonal_path = get_diameter_path(succ, v, curr);

        if (diagonal_path.size() > longest_dia_path.size())
            longest_dia_path = std::move(diagonal_path);

        if (vertical_path.size() >= tallest_path.size())
        {
            second_tallest_path = std::move(tallest_path);
            tallest_path = std::move(vertical_path);
        }
        else if (vertical_path.size() > second_tallest_path.size())
        {
            second_tallest_path = std::move(vertical_path);
        }
    }

    // Return max of following:
    // 1) Max diameter in subtrees
    // 2) Height of longest subtree + height of second longest subtree + 1
    if (tallest_path.size() + second_tallest_path.size() + 1 > longest_dia_path.size())
    {
        tallest_path.push_back(curr);
        for (auto it = second_tallest_path.rbegin(); it != second_tallest_path.rend(); ++it)
            tallest_path.push_back(*it);

        return tallest_path;
    }

    return longest_dia_path;
}

int find_the_optimal_root(int n, std::vector<std::pair<int, int>> const& v)
{ // O(n^2)
    int height, min_height = n;
    int optimal;
    Tree successor(n);
    for (auto& edge : v)
    { // O(n)
        successor[edge.first].push_back(edge.second);
        successor[edge.second].push_back(edge.first);
    }

    auto dp = get_diameter_path(0, successor);

    return dp[dp.size() / 2];
}

int main(int argc, char const* argv[])
{
    /*int n = 4;
    std::vector <std::pair <int, int>> edges = {
        {1, 0},
        {1, 2},
        {1, 3}
    };*/
    /*
         0
       1    2
     3     4  5
       6
      7

    */
    int n = 8;
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {3, 6}, {6, 7}, {2, 4}, {2, 5},
    };

    std::cout << find_the_optimal_root(n, edges) << std::endl;
    return 0;
}
