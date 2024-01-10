# Sparse Vector Implementation

## Task Description

Your task is to implement a `SparseVector` class template in C++. A sparse vector is a vector where most of the elements are zero. The `SparseVector` class should store only non-zero elements to optimize space usage.

### Class Interface

- **Constructor from `std::vector`**: Initialize a `SparseVector` from a `std::vector`, storing only non-zero elements.
- **Copy Constructor**: Initialize a `SparseVector` as a copy of another `SparseVector`.
- **`get` method**: Return a `std::vector` representation of the sparse vector, filling in zero values where appropriate.
- **`operator+=`**: Implement the addition assignment operator to add another `SparseVector` to the current one.

### Constructor Example

```cpp
std::vector<int> v = {0, 1, 0, 3};
SparseVector<int> sv(v);
```

This should result in a `SparseVector` storing elements `{1, 3}` at indices `{1, 3}`.

### Addition Assignment Operator Example

```cpp
SparseVector<int> sv1 = {0, 1, 0, 3};
SparseVector<int> sv2 = {1, 0, 2, 0};
sv1 += sv2;
```

After the addition, `sv1` should represent the vector `{1, 1, 2, 3}`.

## Constraints

- The vectors to be added must be of the same size. If not, an exception should be thrown.
- The `SparseVector` class should be optimized for space, storing only non-zero elements.

## Notes

- Focus on writing clean, efficient, and robust C++ code.
- Consider edge cases, such as adding two vectors where one is completely zero.
- Ensure that the vector returned by the `get` method correctly represents the sparse vector, including zero elements at the appropriate indices.
