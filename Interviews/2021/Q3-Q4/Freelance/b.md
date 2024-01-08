# Carpooling Optimization

## Task Description

Write a function to determine the minimum number of cars required to transport all friends to a holiday destination. A group of friends starts their journey with a set number of cars and seats. The function should optimize the number of cars used to be as eco-friendly as possible, while ensuring that:

- No part of a group is split up.
- Some cars may be left at the starting point if they are not needed.

## Function Signature

```cpp
int solution(std::vector<int>& P, std::vector<int>& S);
```

## Parameters

- `P`: a vector of integers where `P[i]` represents the number of people in the `i`-th car.
- `S`: a vector of integers where `S[i]` represents the number of seats in the `i`-th car.

Both vectors `P` and `S` consist of `N` elements, representing `N` cars.

## Returns

- An integer representing the minimum number of cars needed.

## Constraints

- `N` is an integer within the range [1..100,000].
- Each element of arrays `P` and `S` is an integer within the range [1..9].
- Every friend had a seat in the car they came in; that is, `P[i]` ≤ `S[i]` for each `i` within the range [0..N-1].

## Examples

1. Given `P = [1, 4, 1]` and `S = [1, 5, 1]`, the function should return `2`. The person from the first car can join the second car, allowing the first car to be left behind.

2. Given `P = [4, 4, 2, 4]` and `S = [5, 5, 2, 5]`, the function should return `3`. One person from the third car can join the first car, and the remaining can join the fourth car.

3. Given `P = [2, 3, 4, 2]` and `S = [2, 5, 7, 2]`, the function should return `2`. Passengers from the first car can join the second car, and passengers from the fourth car can join the third car.

## Assumptions

- Write an efficient algorithm for the given constraints.

Focus on writing clean, efficient code, with an emphasis on correctness.
