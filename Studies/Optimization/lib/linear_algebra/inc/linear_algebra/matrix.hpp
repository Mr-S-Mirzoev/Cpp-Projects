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
    template<typename T>
    std::vector<T> slice(const std::vector<T> &v, std::size_t begin, std::size_t end = 0) {
        auto first = v.cbegin() + begin;
        auto last = !end ? v.cend() : v.cbegin() + end;
    
        return std::vector<T>(first, last);
    }

    class Index {
        bool _is_pair = false;
        std::size_t _i, _j;
    public:
        Index (const std::initializer_list <std::size_t> &data):
            _is_pair(true) {
            if (data.size() != 2)
                throw NotAPairException("The size of initializer_list is not 2");

            auto it = data.begin();
            _i = *it;
            ++it;
            _j = *it;
        }

        Index (std::size_t data): _i(data) {}

        std::size_t i() const { return _i; }
        std::size_t j() const {
            if (!_is_pair)
                throw NotAPairException("The second value isn't set");

            return _j; 
        }
        bool is_pair() const { return _is_pair; }
    };
    
    /**
     * Implementation of n*m matrix entity in C++
     */
    class Matrix {
        std::vector <double> _data{0};
        std::size_t _n = 0, _m{0};

        const std::size_t THRESHOLD = 3;

        Matrix& naive_mul(const Matrix &rhs);
        Matrix& mul(const Matrix rhs);
    public:
        Matrix(std::size_t n, std::size_t m = 1): 
            _data(n * m), _n(n), _m(m) {}
        Matrix() {}
        Matrix(const Matrix &rhs): _data(rhs._data), _n(rhs._n), _m(rhs._m) {}
        Matrix(Matrix &&rhs): 
            _data(std::move(rhs._data)), _n(rhs._n), _m(rhs._m) {}

        std::size_t n() const { return _n; }
        std::size_t m() const { return _m; }

        double& operator[](Index idx);
        double  operator[](Index idx) const;
        Matrix& operator=(Matrix &&rhs);
        Matrix& operator=(const Matrix &rhs);
        
        #define ELEMENT_WISE_OPERATION_DEF(NAME) Matrix& NAME(const Matrix &rhs)
        ELEMENT_WISE_OPERATION_DEF(operator+);
        ELEMENT_WISE_OPERATION_DEF(operator-);
        ELEMENT_WISE_OPERATION_DEF(dot);

        Matrix operator*(const Matrix &rhs);
        /**
         * A = this[:idx] (so it has to be > 0)
         * B = this[idx:]
         */
        void split(Matrix *a, Matrix *b, std::size_t idx, bool horizontal = false) const;

        friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
        friend Matrix merge(const Matrix &a, const Matrix &b, bool horizontal);
    };

    Matrix merge(const Matrix &a, const Matrix &b, bool horizontal = false);

} // namespace linear_algebra

#endif // LINALG_MATRIX_HPP