# Description

You are given a 2D matrix with several characters contained in its cells. You will also have two distinct characters which are guaranteed to be in the given matrix. Your job will be to find the minimum manhattan distance between the two characters in the matrix.

The manhattan distance of two points (x1, y1) and (x2, y2) is |x1-x2|+|y1-y2|. In other words, it is the distance between two points measured along axes at right angles.

```
#####################
# - # - # A # - # A #
#####################
# - # A # - # - # - #
#####################
# - # - # - # B # - #
#####################
# A # - # - # - # - #
#####################
# - # A # - # A # A #
#####################
```

For example in the above image:

The result will be 2, because the minimum distance is from A(4,3) to B(2,3)-- which is 2. Note, for the points of the graph, we respect the programming version and use a 0-index.

Constraints:

- Minimum Size of Matrix: $2$ cells (e.g. $1x2$ or $2x1$)
- Maximum Size of Matrix: $10^8$ cells (e.g. $10^4x10^4$)
- The given $2$ characters are guaranteed to appear at least once in the matrix.
- Expected Time Complexity: $O(m*n)$ where $m$ and $n$ are the height and width of matrix.
- Expected Space Complexity: $O(m*n)$.