#include <vector>
#include <numeric>
#include <unordered_map>
#include <iostream>

using NodeID = int;
using Time = int;
constexpr const NodeID NULL_NODE = -1;
constexpr const Time INF = std::numeric_limits<Time>::max();

struct Edge {
    NodeID u;
    NodeID v;
    Time t;
};

std::pair<Time, int> dijkstra(int n, std::vector<Edge> const& edges, NodeID destination, NodeID initial = 0) {
    if (initial == destination)
        return {0, 1};

    // 1. Mark all nodes unvisited. Create a set of all the unvisited nodes called the unvisited set.
    std::unordered_map <NodeID, std::pair<Time, int>> unvisited; // [NodeID]->{min time to node from start; num min paths}
    unvisited.reserve(n);

    /* 2a. Assign to every node a tentative distance value: set it to zero for our initial node and to infinity for all other nodes. The
    tentative distance of a node v is the length of the shortest path discovered so far between the node v and the starting node. Since
    initially no path is known to any other vertex than the source itself (which is a path of length zero), all other tentative distances are
    initially set to infinity. */
    unvisited[initial] = {0, 1};
    for (int i = 1; i < n; ++i)
        unvisited[i] = {INF, 0};

    // 2b. Set the initial node as current.
    NodeID current = initial;

    while (1) {
        /* 3. For the current node, consider all of its unvisited neighbors and calculate their tentative distances through the current node.
        Compare the newly calculated tentative distance to the current assigned value and assign the smaller one. For example, if the current node
        A is marked with a distance of 6, and the edge connecting it with a neighbor B has length 2, then the distance to B through A will be
        6 + 2 = 8. If B was previously marked with a distance greater than 8 then change it to 8. Otherwise, the current value will be kept. */
        for (Edge const& edge : edges) {
            if (edge.u != current && edge.v != current)
                continue;

            NodeID neighbour = (edge.u == current) ? edge.v : edge.u;
            auto it = unvisited.find(neighbour);
            if (it == unvisited.end())
                continue;

            Time time_via_current = unvisited[current].first + edge.t;
            if (it->second.first > time_via_current)
                unvisited[neighbour] = {time_via_current, unvisited[current].second};
            else if (it->second.first == time_via_current)
                unvisited[neighbour].second += unvisited[current].second;
        }

        /* 4. When we are done considering all of the unvisited neighbors of the current node, mark the current node as visited and remove it
        from the unvisited set. A visited node will never be checked again. */
        unvisited.erase(current);
        current = NULL_NODE;

        /* 5. If the destination node has been marked visited (when planning a route between two specific nodes) or if the smallest tentative distance among the nodes in the unvisited set is infinity (when planning a complete traversal; occurs when there is no connection between the initial node and remaining unvisited nodes), then stop. The algorithm has finished. */
        Time min_dist = INF;
        for (auto &el : unvisited) {
            if (el.second.first < min_dist) {
                min_dist = el.second.first;
                current = el.first;
            }
        }

        if (min_dist == INF || min_dist >= unvisited[destination].first)
            return unvisited[destination];

        /* 6. Otherwise, select the unvisited node that is marked with the smallest tentative distance, set it as the new current node, and go
        back to step 3. */
    }
}

/*
You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.

You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.

Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.
*/

int countPaths(int n, std::vector<std::vector<int>> const& roads) {
    std::vector<Edge> edges;
    std::size_t sz = roads.size();
    edges.resize(sz);
    for (int i = 0; i < sz; ++i)
        edges[i] = {roads[i][0], roads[i][1], roads[i][2]};
    
    auto result = dijkstra(n, edges, n - 1);
    return result.second;
}

int main(int argc, char const *argv[]) {
    /*
    int n = 7;
    std::vector<std::vector<int>> roads = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
    */
    int n = 2;
    std::vector<std::vector<int>> roads = {{1, 0, 10}};
    std::cout << countPaths(n, roads) << std::endl;
    return 0;
}
