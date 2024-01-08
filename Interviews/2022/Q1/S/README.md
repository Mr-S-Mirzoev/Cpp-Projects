# Optimal Tree Root Finder

## Task

Given a tree represented as an undirected graph with `n` nodes, find the node(s) that minimize the height of the tree when used as the root.

## Definitions

- **Tree**: A connected acyclic undirected graph.
- **Height of a Tree**: The length of the longest path from the root to a leaf.
- **Root of a Tree**: A node from which every other node is accessible through a unique path.

## Input

- `n`: An integer representing the number of nodes in the tree.
- `edges`: A list of pairs of integers, where each pair represents an undirected edge between two nodes.

## Output

An integer representing the node that minimizes the tree's height when chosen as the root.

## Examples

### Example 1

```
Input: n = 4, edges = [[1,0],[1,2],[1,3]]

   0
   |
   1
  / \
 2   3

Output: 1
```

The optimal root is node `1` because choosing it minimizes the height of the tree.

### Example 2

```
Input: n = 8, edges = [[0,1],[0,2],[1,3],[3,6],[6,7],[2,4],[2,5]]

     0
   /   \
  1     2
 /     / \
3     4   5
 \
  6
   \
    7

Output: 1
```

Node `1` is the optimal root as it results in the minimum height of the tree.

## Constraints

- `1 <= n <= 10^5`
- `n-1 == edges.size()`, ensuring the input forms a valid tree.
