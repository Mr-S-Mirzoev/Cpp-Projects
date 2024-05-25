### Algorithm Explanation

The algorithm involves two main parts: precomputing the cumulative distances and times for each interval and then finding the time required to reach given distances using this precomputed data.

#### 1. Precomputing Distances and Times
This part of the algorithm processes the speed intervals to compute the cumulative distance and time at the end of each interval.

**Time Complexity**:
   - Iterating over the $N$ intervals: $O(N)$
   - Total: $O(N)$

#### 2. Finding Time for Given Distances
This part of the algorithm uses the precomputed data to quickly find the time required to reach each queried distance.

- **Binary Search for Interval**: For each distance query $ d $:
  - Use `std::lower_bound` to find the first precomputed point where the cumulative distance is not less than $ d $.
  - If the exact distance is found in the precomputed data, directly return the corresponding time.
  - If the exact distance is not found, use the previous interval's data to compute the remaining time to reach the distance $ d $:
    - Calculate the remaining distance $ d - \text{start_distance} $.
    - If the acceleration is zero, the remaining time is $ \frac{\text{remaining_distance}}{\text{start_velocity}} $.
    - If there is acceleration, solve the quadratic equation $ \frac{a}{2} t^2 + v t = \text{remaining_distance} $ for $ t $ and take the positive solution

**Time Complexity**:
   - For each of the $Q$ queries, using binary search: $O(\log N)$
   - Total for $Q$ queries: $O(Q \log N)$

### Code Explanation

The provided code implements the above algorithm:

- Function `compute_distances_and_times` computes the cumulative distances and times for each interval
- Function `find_time_for_distance` finds the time for given distances using the precomputed data
- Function `compute_remaining_time` computes the remaining time to reach a distance

### Time and Space Complexity

Overall Time Complexity: $O(N + Q \log N)$

**Space Complexity**:
- Storing the speed intervals: $O(N)$
- Storing the cumulative distances and times: $O(N)$
- Storing the query results: $O(Q)$

Overall Space Complexity: $O(N + Q)$
