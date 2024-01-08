# Pollution Reduction in Industrial Factories

## Task Description

An industrial company with `N` factories aims to reduce its overall pollution by equipping factories with pollution filters. Each filter reduces a factory's pollution output by half. The goal is to find the minimum number of filters needed to reduce the total pollution by at least half.

## Function Signature

```cpp
int solution(std::vector<int>& A);
```

## Parameters

- `A`: a vector of integers where `A[i]` represents the amount of pollution produced by the `i`-th factory.

## Returns

- An integer representing the minimum number of filters required to achieve the goal.

## Constraints

- `N` is an integer within the range [1..30,000].
- Each element of array `A` is an integer within the range [0..70,000].

## Examples

1. Given `A = [5, 19, 8, 1]`, the function should return `3`. By installing two filters at the factory producing 19 units and one filter at the factory producing 8 units, the total pollution can be reduced to less than half.

2. Given `A = [10, 10]`, the function should return `2`. One filter can be installed at each factory.

3. Given `A = [3, 0, 5]`, the function should return `2`. Filters should be installed at the factories producing a non-zero amount of pollution.

## Assumptions

- Write an efficient algorithm for the given constraints.

Emphasize writing clean and efficient code, with a focus on correctness and performance.
