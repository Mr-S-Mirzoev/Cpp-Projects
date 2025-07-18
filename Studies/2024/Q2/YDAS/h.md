### Task H: Important Roads

#### Problem Description

In a certain game, the map consists of $ n $ cities, numbered from 1 to $ n $. The starting city is city 1, referred to as the capital. Some cities are connected by roads that allow travel in both directions. Each road has a positive length. The roads are not necessarily straight, so there can be multiple roads between the same pair of cities. For simplicity, roads only intersect at cities.

Not all roads are shown on the map; some are listed on special additional cards in the game. The road system is designed such that it is possible to travel between any pair of cities using the roads. No road connects a city to itself.

To optimize road taxes, the player needs to keep as few active roads as possible (both on the map and on the special cards). However, the player must ensure that it is possible to reach any city from the capital using the shortest possible path considering all roads. The shortest path is defined as the path with the minimum length, where the length of a path is the sum of the lengths of all roads in that path.

Determine the number of roads that must be kept by the player in any case. In other words, identify the number of roads such that if any one of these roads is removed, there will be at least one city where the shortest path from the capital changes.

#### Input Format

1. The first line contains two integers $ n $ and $ m $ (2 ≤ $ n $ ≤ 100, 1 ≤ $ m $ ≤ 1000) — the number of cities and roads in the game.
2. The next $ m $ lines each contain three integers $ x_i, y_i $ and $ l_i $ (1 ≤ $ x_i, y_i $ ≤ $ n $, $ x_i \neq y_i $, 1 ≤ $ l_i $ ≤ $ 10^6 $) — the cities connected by the road and the length of the road.

#### Output Format

Output a single integer — the number of roads that must necessarily be kept in the game.

#### Example

**Input:**
```
2 3
2 1 111111
1 2 1000000
1 2 113
```

**Output:**
```
1
```

**Input:**
```
5 7
2 1 18
5 1 21
2 3 10
3 1 7
2 4 8
3 5 10
2 5 5
```

**Output:**
```
4
```

**Input:**
```
5 7
2 3 10
1 5 7
3 5 1
4 2 5
1 2 16
4 3 5
3 1 6
```

**Output:**
```
2
```

#### Notes

The problem will be evaluated for the optimality of the proposed algorithm in terms of time and memory. Points for the textual description of the algorithm may be deducted if the last successful submission contains an implementation that does not match the described algorithm.

#### Constraints

- Time limit: 2 seconds
- Memory limit: 256 MB

#### Task Objective

The objective is to determine the number of critical roads in the graph. A critical road is one whose removal would result in a longer shortest path from the capital (city 1) to any other city. The solution must be optimized to handle the input constraints efficiently.
