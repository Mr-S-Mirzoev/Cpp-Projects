#pragma once

#include "tree.h"

using TreePath = std::vector<int>;

class TreePathUtils
{
    int nodes_count_;
    AdjacencyList adj_list_;

public:
    TreePathUtils(Edges const& edges, int n);

    /**
     * @brief Returns the path from the current node to the farthest leaf. Only takes into account
     * the height of the tree.
     *
     */
    TreePath get_tallest_path(int curr, int prev = -1) const;

    /**
     * @brief Returns the path from the current node to the farthest leaf. Takes into account the
     * diameter of the tree and not just the height.
     *
     * @note The diameter of a tree is the number of nodes on the longest path between two leaves in
     * the tree.
     *
     * @note This method takes O(n^2) time, where `n` is the number of nodes in subtree with the
     * root in `cur`
     *
     * @return Path which is max of following:
     * 1) Max diameter in subtrees
     * 2) Height of longest subtree + height of second longest subtree + 1
     *
     */
    TreePath get_diameter_path(int curr, int prev = -1) const;

    /**
     * @brief Returns the diameter path from the two longest subtrees.
     *
     * @param tallest_path Path from the current node to the farthest leaf.
     * @param second_tallest_path Path from the current node to the second farthest leaf.
     * @param curr The current node, which is the mutual parent of the given paths.
     */
    void get_diameter_path_from_two_longest_subtrees(TreePath& tallest_path,
                                                     TreePath& second_tallest_path, int curr) const;
};