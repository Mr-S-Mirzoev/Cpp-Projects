#pragma once

#include <map>
#include <vector>

template <typename T>
class SparseVector
{
    std::map<std::size_t, T> data_{};
    std::size_t size_ = 0;

public:
    SparseVector() = default;

    SparseVector(std::vector<T> const& v);
    SparseVector(SparseVector const& other);

    std::vector<T> get() const;
    SparseVector& operator+=(SparseVector const& other);
};
