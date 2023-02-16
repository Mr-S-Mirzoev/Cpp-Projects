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

            *this = merge(A1->mul(rhs), A2->mul(rhs), true);
            return *this;
        } else if (_max == rhs._m) {
            std::unique_ptr<Matrix> B1{new Matrix()}, B2{new Matrix()};
            rhs.split(B1.get(), B2.get(), rhs._m / 2);

            Matrix cpy(*this);
            cpy.mul(*B1);

            *this = merge(cpy, mul(*B2));
            return *this;
        } else {
            std::unique_ptr<Matrix> A1{new Matrix()}, A2{new Matrix()};
            split(A1.get(), A2.get(), _m / 2);

            std::unique_ptr<Matrix> B1{new Matrix()}, B2{new Matrix()};
            rhs.split(B1.get(), B2.get(), rhs._n / 2, true);

            *this = A1->mul(*B1) + A2->mul(*B2);
            return *this;
        }
    }

    bool Matrix::operator==(const Matrix &rhs) const {
        if (rhs._m != _m || rhs._n != _n)
            return false;
        
        auto it = _data.begin();
        auto rit = rhs._data.begin();

        for (; it != _data.end() && rit != rhs._data.end(); ++it, ++rit)
            if (std::abs(*it - *rit) > EPS)
                return false;

        return true;
    }

    Matrix& Matrix::inverse() {
        if (_n != _m)
            throw NotSquareException(_n, _m);
        
        Matrix aug = merge(*this, eye(_n));

        /* Applying Gauss Jordan Elimination */
        for (std::size_t i = 0; i < _n; ++i) {
            if (std::abs(aug[{i, i}]) < 1e-5)
                throw ZeroDeterminantException();
            
            for (std::size_t j = 0; j < _n; ++j) {
                if (i != j) {
                    double ratio = aug[{j, i}] / aug[{i, i}];
                    for (std::size_t k = 0; k < 2 * _n; ++k)
                        aug[{j, k}] -= ratio * aug[{i, k}];
                }
            }
        }

        /* Row Operation to Make Principal Diagonal to 1 */
        for (std::size_t i = 0; i < _n; ++i)
            for (std::size_t j = _n; j < 2 * _n; ++j)
                aug[{i, j}] /= aug[{i, i}];

        std::unique_ptr<Matrix> Eye{new Matrix()}, Inv{new Matrix()};
        aug.split(Eye.get(), Inv.get(), _n);

        *this = Matrix(*Inv);
        return *this;
    }

    Matrix& Matrix::pow(int pow) {
        if (pow == 0) {
            *this = Matrix(_n, 1.);
            return *this;
        }

        if (_n != _m)
            throw NotSquareException(_n, _m);

        if (pow < 0) {
            inverse();
            pow = -pow;
        }

        Matrix result = eye(_n);

        while (pow > 1) {
            if (pow % 2 == 0) {
                mul(*this);
                pow = pow / 2;
            } else {
                result.mul(*this);
                mul(*this);
                pow = (pow - 1) / 2;
            }
        }

        result.mul(*this);
        *this = result;
        return *this;
    }

    Matrix Matrix::operator^(int pow) {
        Matrix cpy(*this);
        cpy.pow(pow);
        return cpy;
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

    Matrix eye(std::size_t n, double val) {
        Matrix proto(n, n);
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                proto[{i, j}] = (i == j) ? val : .0;
            }
        }

        return proto;
    }

} // namespace linear_algebra
