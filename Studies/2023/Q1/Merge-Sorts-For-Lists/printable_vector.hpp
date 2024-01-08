#pragma once

#include "printable.hpp"

#include <vector>

template <Printable T>
class PrintableVector : public std::vector<T>
{
public:
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const PrintableVector<U>& other);
};

template <Printable T>
std::ostream& operator<<(std::ostream& os, const PrintableVector<T>& v)
{
    os << "{ ";
    for (const auto& el : v)
        os << el << " ";
    os << "}";
    return os;
}
