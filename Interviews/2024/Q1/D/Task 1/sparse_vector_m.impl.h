#pragma once

#include "sparse_vector.h"

#include <stdexcept>

template <typename T>
using SparseVectorMBased = SparseVector<T, ImplementationType::MapBased>;

template <typename T>
class SparseVector<T, ImplementationType::MapBased>
{
    std::map<std::size_t, T> data_{};
    std::size_t size_ = 0;

public:
    SparseVector() = default;

    SparseVector(std::vector<T> const& v);
    SparseVector(SparseVector const& other);

    std::vector<T> get() const;
    SparseVector& operator+=(SparseVector const& other);

    friend SparseVector operator+(SparseVector const& lhs, SparseVector const& rhs)
    {
        SparseVector res = lhs;
        res += rhs;
        return res;
    }
};

template <typename T>
SparseVectorMBased<T>::SparseVector(std::vector<T> const& v) : size_(v.size())
{
    for (int i = 0; i < size_; ++i)
    {
        if (v[i])
        {
            data_.emplace_hint(data_.end(), i, v[i]);
        }
    }
}

template <typename T>
SparseVectorMBased<T>::SparseVector(SparseVector const& other)
    : data_(other.data_), size_(other.size_)
{
}

template <typename T>
std::vector<T> SparseVectorMBased<T>::get() const
{
    std::vector<T> res(size_);
    for (const auto& [i, el] : data_)
    {
        res[i] = el;
    }

    return res;
}

template <typename T>
SparseVectorMBased<T>& SparseVectorMBased<T>::operator+=(SparseVector const& other)
{
    if (size_ != other.size_)
    {
        throw std::runtime_error("SparseVector size mismatch");
    }

    if (data_.empty())
    {
        data_ = other.data_;
        return *this;
    }

    if (other.data_.empty())
    {
        return *this;
    }

    auto it = data_.begin();
    auto other_it = other.data_.begin();

    while (it != data_.end() && other_it != other.data_.end())
    {
        if (it->first < other_it->first)
        {
            ++it;
            continue;
        }

        if (it->first > other_it->first)
        {
            data_.emplace_hint(it, other_it->first, other_it->second);
        }
        else if (it->first == other_it->first)
        {
            it->second += other_it->second;
            if (!it->second)
            {
                it = data_.erase(it);
            }
            else
            {
                ++it;
            }
        }

        ++other_it;
    }

    while (other_it != other.data_.end())
    {
        data_.emplace_hint(data_.end(), other_it->first, other_it->second);
        ++other_it;
    }

    return *this;
}
