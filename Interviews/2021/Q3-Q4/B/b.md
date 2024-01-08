# Maximum Product Path in a Binary Heap

## Task Description

Given a binary heap where each node contains an integer value, determine the maximum product that can be obtained by multiplying the values along the path between any two leaves in the heap.

## Input

- The first line contains an integer `N`, the number of nodes in the binary heap.
- The next `N` lines each contain an integer representing the value of each node in the order of node indices (1-based index).
- The next `N - 1` lines each contain two integers `parent` and `child`, indicating that the `child` is a child of `parent` in the heap (1-based index).

## Output

- Output a single integer, the maximum product of the values along the path between any two leaves.

## Constraints

- The heap is a binary heap.
- The values of the nodes are positive integers.

## Example

### Input

```
5
2
3
7
4
5
1 2
1 3
2 4
2 5
```

### Binary Heap Representation

```
     2
    / \
   3   7
  / \
 4   5
```

### Output

```
140
```

In this example, the maximum product is obtained along the path between leaf node 4 and leaf node 7, which is `4 * 3 * 2 * 7 = 140`.
