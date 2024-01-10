#pragma once

#include "sparse_vector.h"

#include <stdexcept>

template <typename T>
using SparseVectorVBased = SparseVector<T, ImplementationType::VectorBased>;

template <typename T>
class SparseVector<T, ImplementationType::VectorBased>
{
    std::vector<std::pair<std::size_t, T>> data_{};
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
SparseVectorVBased<T>::SparseVector(std::vector<T> const& v) : size_(v.size())
{
    for (int i = 0; i < size_; ++i)
    {
        if (v[i])
        {
            data_.emplace_back(i, v[i]);
        }
    }
}

template <typename T>
SparseVectorVBased<T>::SparseVector(SparseVector const& other)
    : data_(other.data_), size_(other.size_)
{
}

template <typename T>
std::vector<T> SparseVectorVBased<T>::get() const
{
    std::vector<T> res(size_);
    for (const auto& [i, el] : data_)
    {
        res[i] = el;
    }

    return res;
}

template <typename T>
SparseVectorVBased<T>& SparseVectorVBased<T>::operator+=(SparseVector const& other)
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

    std::vector<std::pair<std::size_t, T>> new_data(data_.size() + other.data_.size());
    while (it != data_.end() && other_it != other.data_.end())
    {
        if (it->first < other_it->first)
        {
            new_data.emplace_back(std::move(it->first), std::move(it->second));
            ++it;
            continue;
        }

        if (it->first > other_it->first)
        {
            new_data.emplace_back(other_it->first, other_it->second);
        }
        else if (it->first == other_it->first)
        {
            const auto new_value = it->second + other_it->second;
            if (it->second)
            {
                new_data.emplace_back(std::move(it->first), std::move(it->second));
            }

            ++it;
        }

        ++other_it;
    }

    if (it != data_.end())
    {
        std::move(it, data_.end(), std::back_inserter(new_data));
    }
    else if (other_it != other.data_.end())
    {
        std::copy(other_it, other.data_.end(), std::back_inserter(new_data));
    }

    data_ = std::move(new_data);
    return *this;
}
