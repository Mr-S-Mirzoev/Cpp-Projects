#include "sparse_vector.h"

template <typename T>
SparseVector<T>::SparseVector(std::vector<T> const& v) : size(v.size())
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
SparseVector<T>::SparseVector(SparseVector const& other) : data_(other.data_), size_(other.size_)
{
}

template <typename T>
std::vector<T> SparseVector<T>::get() const
{
    std::vector<T> res{size, T{}};
    for (const auto& [i, el] : data_)
    {
        res[i] = el;
    }

    return res;
}

template <typename T>
SparseVector<T>& SparseVector<T>::operator+=(SparseVector const& other)
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

    if (other.empty())
    {
        return *this;
    }

    auto it = data_.begin();
    auto other_it = other.data_.begin();

    while (it != data_.end() && other_it != other.data_.end())
    {
        if (it->first > other_it->first)
        {
            data_.emplace_hint(it, other_it->first, other_it->second);
            ++other_it;
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
            ++other_it;
        }
        else
        {
            ++it;
        }
    }

    while (other_it != other.data_.end())
    {
        data_.emplace_hint(data_.end(), other_it->first, other_it->second);
        ++other_it;
    }

    return *this;
}
