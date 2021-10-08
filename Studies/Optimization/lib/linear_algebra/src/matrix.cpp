#include "linear_algebra/matrix.hpp"

#include <algorithm>
#include <memory>

namespace linear_algebra
{
    
    Matrix& Matrix::naive_mul(const Matrix &rhs) {
        if (rhs._n != _m)
            throw SizeMismatchException("*", _n, _m, rhs._n, rhs._m);

        Matrix C(_n, rhs._m);
        
        for (std::size_t i = 0; i < _n; i++) {
            for (std::size_t j = 0; j < rhs._m; j++) {
                C[{i, j}] = 0;
                for (std::size_t k = 0; k < _m; k++)
                    C[{i, j}] +=(*this)[{i, k}] * rhs[{k, j}];
            }
        }

        *this = C;

        return (*this);
    }

    Matrix& Matrix::mul(Matrix rhs) {
        if (rhs._n != _m)
            throw SizeMismatchException("*", _n, _m, rhs._n, rhs._m);

        std::size_t _min = std::min({_n, _m, rhs._m});
        std::size_t _max = std::max({_n, _m, rhs._m});

        if (_min == 1 || _max <= 3)
            return naive_mul(rhs);

        if (_max == _n) {
            std::unique_ptr<Matrix> A1{new Matrix()}, A2{new Matrix()};
            split(A1.get(), A2.get(), _n / 2, true);

            std::cout << "Case A:" << std::endl;
            std::cout << *A1 << std::endl << std::endl;
            std::cout << *A2 << std::endl << std::endl;


            *this = merge(A1->mul(rhs), A2->mul(rhs), true);
            return *this;
        } else if (_max == rhs._m) {
            std::unique_ptr<Matrix> B1{new Matrix()}, B2{new Matrix()};
            rhs.split(B1.get(), B2.get(), rhs._m / 2);

            std::cout << "Case B:" << std::endl;
            std::cout << *B1 << std::endl << std::endl;
            std::cout << *B2 << std::endl << std::endl;

            Matrix cpy(*this);
            cpy.mul(*B1);

            *this = merge(cpy, mul(*B2));
            return *this;
        } else {
            std::unique_ptr<Matrix> A1{new Matrix()}, A2{new Matrix()};
            split(A1.get(), A2.get(), _m / 2);

            std::unique_ptr<Matrix> B1{new Matrix()}, B2{new Matrix()};
            rhs.split(B1.get(), B2.get(), rhs._n / 2, true);

            std::cout << "Case C:" << std::endl;
            std::cout << *this << std::endl << std::endl;
            std::cout << rhs << std::endl << std::endl;
            std::cout << *A1 << std::endl << std::endl;
            std::cout << *A2 << std::endl << std::endl;
            std::cout << *B1 << std::endl << std::endl;
            std::cout << *B2 << std::endl << std::endl;

            *this = A1->mul(*B1) + A2->mul(*B2);
            return *this;
        }
    }

    Matrix Matrix::operator*(const Matrix &rhs) {
        Matrix cpy(*this);
        cpy.mul(rhs);
        return cpy;
    }
    
    Matrix& Matrix::operator=(const Matrix &rhs) {
        _data = rhs._data;
        _n = rhs._n;
        _m = rhs._m;

        return *this;
    }

    Matrix& Matrix::operator=(Matrix &&rhs) {
        _data = std::move(rhs._data);
        _n = rhs._n;
        _m = rhs._m;

        return *this;
    }
    
    double& Matrix::operator[](Index idx) {
        if (!idx.is_pair()) {
            if (_m != 1)
                throw NotAVectorException();

            auto i = idx.i();
            if (i >= _n)
                throw IndexOutOfRangeException(i, _n);

            return _data[i];
        }

        auto i = idx.i();
        auto j = idx.j();

        if (i >= _n || j >= _m)
            throw IndexOutOfRangeException(i, j, _n, _m);

        return _data[i * _m + j];
    }

    double Matrix::operator[](Index idx) const {
        if (!idx.is_pair()) {
            if (_m != 1)
                throw NotAVectorException();

            auto i = idx.i();
            if (i >= _n)
                throw IndexOutOfRangeException(i, _n);

            return _data[i];
        }

        auto i = idx.i();
        auto j = idx.j();

        if (i >= _n || j >= _m)
            throw IndexOutOfRangeException(i, j, _n, _m);

        return _data[i * _m + j];
    }

    #define ELEMENT_WISE_OPERATION_IMPL(NAME, OP)                               \
    Matrix& Matrix::NAME(const Matrix &rhs) {                                   \
        if (rhs._n != _n || rhs._m != _m)                                       \
            throw SizeMismatchException(#OP, _n, _m, rhs._n, rhs._m);           \
                                                                                \
        for (std::size_t i = 0; i < _n; ++i) {                                  \
            std::size_t row_shift = i * _m;                                     \
                                                                                \
            for (std::size_t j = 0; j < _m; ++j)                                \
                _data[row_shift + j] OP rhs._data[row_shift + j];               \
        }                                                                       \
                                                                                \
        return *this;                                                           \
    }

    ELEMENT_WISE_OPERATION_IMPL(operator+,+=);
    ELEMENT_WISE_OPERATION_IMPL(operator-,+=);
    ELEMENT_WISE_OPERATION_IMPL(dot,*=);

    void Matrix::split(Matrix *a, Matrix *b, std::size_t idx, bool horizontal) const {
        //std::cout << idx << ' ' << horizontal << ' ' << _n << ' ' << _m << std::endl;

        if (horizontal) {
            Matrix _a(idx, _m), _b(_n - idx, _m);

            _a._data = slice(_data, 0, idx * _m);
            _b._data = slice(_data, idx * _m);

            *a = _a;
            *b = _b;
        } else {
            Matrix _a(_n, idx), _b(_n, _m - idx);
            std::size_t a_l = 0, b_l = 0;
            for (int i = 0; i < _n; ++i) {
                for (int j = 0; j < _m; ++j) {
                    if (j < idx) {
                        _a._data[a_l++] = _data[i * _m + j];
                    } else {
                        _b._data[b_l++] = _data[i * _m + j];
                    }
                }
            }

            *a = _a;
            *b = _b;
        }
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        // Print first row
        os << m._data[0];
        for (std::size_t j = 1; j < m._m; j++) {
            os << " " << m._data[j];
        }

        // Print the rest of the rows
        for (std::size_t i = 1; i < m._n; i++) {
            os << std::endl << m._data[i * m._m];
            for (std::size_t j = 1; j < m._m; j++) {
                os << " " << m._data[i * m._m + j];
            }
        }

        return os;
    }

    Matrix merge(const Matrix &a, const Matrix &b, bool horizontal) {
        if (horizontal) {
            Matrix c (a._n + b._n, a._m);

            std::copy(a._data.begin(), a._data.end(), c._data.begin());
            std::copy(b._data.begin(), b._data.end(), c._data.begin() + a._data.size());

            return c;
        } else {
            Matrix c (a._n, a._m + b._m);
            std::size_t a_l = 0, b_l = 0;
            for (std::size_t i = 0; i < c._n; ++i) {
                for (std::size_t j = 0; j < c._m; ++j) {
                    if (j < a._m) {
                        c[{i, j}] = a._data[a_l++];
                    } else {
                        c[{i, j}] = b._data[b_l++];
                    }
                }
            }

            return c;
        }
    }
} // namespace linear_algebra
