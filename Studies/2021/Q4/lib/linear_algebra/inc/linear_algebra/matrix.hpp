#ifndef LINALG_MATRIX_HPP
#define LINALG_MATRIX_HPP

#include <initializer_list>
#include <iostream>
#include <vector>

#include "exceptions.hpp"

namespace linear_algebra
{

/**
 * same as a[1:4] in python
 */
template <typename T>
std::vector<T> slice(const std::vector<T>& v, std::size_t begin, std::size_t end = 0)
{
    auto first = v.cbegin() + begin;
    auto last = !end ? v.cend() : v.cbegin() + end;

    return std::vector<T>(first, last);
}

template <typename T>
std::vector<T> flatten(const std::vector<std::vector<T>>& vecs)
{
    std::size_t to_allocate = 0;
    for (auto v : vecs)
    {
        to_allocate += v.size();
    }
    std::vector<T> result;
    result.reserve(to_allocate);

    for (auto it = vecs.begin(); it != vecs.end(); ++it)
        result.insert(result.end(), it->begin(), it->end());

    return result;
}

class Index
{
    bool _is_pair = false;
    std::size_t _i, _j;

public:
    Index(const std::initializer_list<std::size_t>& data) : _is_pair(true)
    {
        if (data.size() != 2)
            throw NotAPairException("The size of initializer_list is not 2");

        auto it = data.begin();
        _i = *it;
        ++it;
        _j = *it;
    }

    Index(std::size_t data) : _i(data) {}

    std::size_t i() const { return _i; }
    std::size_t j() const
    {
        if (!_is_pair)
            throw NotAPairException("The second value isn't set");

        return _j;
    }
    bool is_pair() const { return _is_pair; }
};

/**
 * Implementation of n*m matrix entity in C++
 */
class Matrix
{
    const std::size_t THRESHOLD = 3;
    const double EPS = 1e-2;

    Matrix& naive_mul(const Matrix& rhs);
    Matrix& mul(const Matrix rhs);

protected:
    std::vector<double> _data{0};
    std::size_t _n = 0, _m{0};

    Matrix& inverse();
    Matrix& pow(int pow);

public:
    Matrix() {}
    Matrix(std::size_t n, std::size_t m = 1) : _data(n * m), _n(n), _m(m) {}
    Matrix(const Matrix& rhs) : _data(rhs._data), _n(rhs._n), _m(rhs._m) {}
    Matrix(Matrix&& rhs) : _data(std::move(rhs._data)), _n(rhs._n), _m(rhs._m) {}

    /**
     * DO NOT USE THIS FUNCTION FOR ANYTHING EXCEPT TESTING!
     */
    Matrix(const std::vector<std::vector<double>>& matrix)
        : _data(flatten(matrix)), _n(matrix.size())
    {
        if (_n == 0)
            throw IrrationalSpaceUsageException();

        _m = matrix[0].size();

        for (auto v : matrix)
            if (v.size() != _m)
                throw SizeMismatchException("Matrix(const std::vector<std::vector<double>>)", 1, _m,
                                            1, v.size());
    }

    std::size_t n() const { return _n; }
    std::size_t m() const { return _m; }

    double& operator[](Index idx);
    double operator[](Index idx) const;
    Matrix& operator=(Matrix&& rhs);
    Matrix& operator=(const Matrix& rhs);
    bool operator==(const Matrix& rhs) const;

#define ELEMENT_WISE_OPERATION_DEF(NAME) Matrix& NAME(const Matrix& rhs)
    ELEMENT_WISE_OPERATION_DEF(operator+);
    ELEMENT_WISE_OPERATION_DEF(operator-);
    ELEMENT_WISE_OPERATION_DEF(dot);

    Matrix operator*(const Matrix& rhs);
    Matrix operator^(int pow);
    /**
     * A = this[:idx] (so it has to be > 0)
     * B = this[idx:]
     */
    void split(Matrix* a, Matrix* b, std::size_t idx, bool horizontal = false) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    friend Matrix merge(const Matrix& a, const Matrix& b, bool horizontal);
};

Matrix merge(const Matrix& a, const Matrix& b, bool horizontal = false);
Matrix eye(std::size_t n, double val = 1.);

} // namespace linear_algebra

#endif // LINALG_MATRIX_HPP