#include "optimal_root.h"

#include "tree_path.h"

int find_optimal_root(Edges const& edges, int nodes_count)
{
    TreePathUtils utils(edges, nodes_count);

    auto dp = utils.get_diameter_path(0);
    int optimal = dp[dp.size() / 2];
    return optimal;
}
