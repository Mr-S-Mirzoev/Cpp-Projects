#include "tree_path.h"

TreePathUtils::TreePathUtils(Edges const& edges, int n) : adj_list_(n), nodes_count_(n)
{
    for (auto& edge : edges) // this loop takes O(n) time
    {
        adj_list_[edge.first].push_back(edge.second);
        adj_list_[edge.second].push_back(edge.first);
    }
}

TreePath TreePathUtils::get_tallest_path(int curr, int prev) const
{
    int next;
    TreePath current_path;

    for (int succ : adj_list_[curr])
    {
        if (prev != -1 && succ == prev)
            continue;

        auto tallest_path = get_tallest_path(succ, curr);
        if (tallest_path.size() > current_path.size())
        {
            next = succ;
            current_path = std::move(tallest_path);
        }
    }

    current_path.push_back(curr);
    return current_path;
}

TreePath TreePathUtils::get_diameter_path(int curr, int prev) const
{
    // base case where tree is empty
    if (adj_list_[curr].size() == 0)
        return {curr};

    TreePath tallest_path;
    TreePath second_tallest_path;
    TreePath longest_dia_path;

    for (int succ : adj_list_[curr])
    {
        if (prev != -1 && succ == prev)
            continue;

        auto vertical_path = get_tallest_path(succ, curr);
        auto diagonal_path = get_diameter_path(succ, curr);

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
    const auto longest_diameter_in_subtrees = longest_dia_path.size();
    const auto sum_of_heights_of_two_longest_subtrees =
        tallest_path.size() + second_tallest_path.size() + 1;
    if (longest_diameter_in_subtrees > sum_of_heights_of_two_longest_subtrees)
        return longest_dia_path;

    get_diameter_path_from_two_longest_subtrees(tallest_path, second_tallest_path, curr);

    return tallest_path;
}

void TreePathUtils::get_diameter_path_from_two_longest_subtrees(TreePath& tallest_path,
                                                                TreePath& second_tallest_path,
                                                                int curr) const
{
    tallest_path.push_back(curr);
    for (auto it = second_tallest_path.rbegin(); it != second_tallest_path.rend(); ++it)
        tallest_path.push_back(*it);
}
