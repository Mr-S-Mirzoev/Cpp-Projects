### Task G: Speed Law

In the modeling of moving objects, there is a concept called the speed law. It is represented as a sequential set of time half-intervals \([l_i, r_i)\) during which the object moves along a straight line with an acceleration \(a_i \geq 0\).

The experimenters want to know the time \(t\) at which the object will be at a distance \(d\). Since there are many interesting moments in time, you need to help them.

Write a program that, given the speed law and distances \(d\), finds the necessary times \(t\).

Initially, the object is located at position \(x = 0\) with zero initial velocity.

### Input Format

- The first line contains a natural number \(N\) \((1 \leq N \leq 10^5)\) — the number of intervals in the speed law.
- The next \(N\) lines contain three integers \(l_i, r_i, a_i\). It is guaranteed that \(0 \leq l_i < r_i = l_{i+1} \leq 10^7\) and \(0 \leq a_i \leq 10^2\), \(a_1 > 0\).
- The next line contains a natural number \(Q\) \((1 \leq Q \leq 10^5)\) — the number of time queries by distance.
- The following \(Q\) lines each contain one integer \(d_i\) \((0 < d_i \leq 10^{18})\) — distance queries for which the time must be answered.

It is guaranteed that the distance queries are such that they are achievable by the time \(r_N\) and the times will be integers.

### Output Format

Output \(Q\) integers, each on a new line. The \(i\)-th line should contain the answer to the \(i\)-th query.

### Example

**Input:**
```
4
0 2 1
2 4 0
4 6 2
6 7 0
5
20
2
9
4
6
```

**Output:**
```
7
2
5
3
4
```

### Notes

The problem will be evaluated for the optimality of the proposed algorithm: in terms of time and memory. Points for the textual description of the algorithm may be deducted if the last successful submission contains an implementation that does not match the described algorithm. The time complexity of your algorithm concerning \(l_i, r_i\) should be sublinear.

### Constraints

- Time limit: 3 seconds
- Memory limit: 128 MB
- Language: Any language is allowed

### Task Objective

The objective is to determine the times \(t\) at which the object reaches specified distances \(d\) based on the given intervals of acceleration. The solution must be optimized for performance to handle the upper constraints effectively.
