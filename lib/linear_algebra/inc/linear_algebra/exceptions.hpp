#ifndef LINALG_EXCEPTION_HPP
#define LINALG_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace linear_algebra
{

    class LinearAlgebraException: public std::logic_error {
    public:
        LinearAlgebraException(const std::string &s): std::logic_error (s) {}
    }; // class LinearAlgebraException

    class SizeMismatchException: public LinearAlgebraException {
    public:
        SizeMismatchException(const std::string &op, 
                            std::size_t n1, std::size_t m1, 
                            std::size_t n2, std::size_t m2):
            LinearAlgebraException("Sizes mismatch in" + op + ": " + 
                                    std::to_string(n1) + "x" + std::to_string(m1) + 
                                    " " + op + " " +
                                    std::to_string(n2) + "x" + std::to_string(m2)) {}
    }; // class SizeMismatchException

    class NotAVectorException: public LinearAlgebraException {
    public:
        NotAVectorException():
            LinearAlgebraException("Not a vector! Trying to apply non-vector operation to a vector") {}
    }; // class NotAVectorException

    class NotAPairException: public LinearAlgebraException {
    public:
        NotAPairException(const std::string &s):
            LinearAlgebraException("Not a pair! " + s) {}
    }; // class NotAPairException

    class NotSquareException: public LinearAlgebraException {
    public:
        NotSquareException(std::size_t n, std::size_t m):
            LinearAlgebraException("Not a square matrix! Trying to apply square op to a " + 
                                    std::to_string(n) + "x" + std::to_string(m) + " matrix." ) {}
    }; // class NotSquareException

    class ZeroDeterminantException: public LinearAlgebraException {
    public:
        ZeroDeterminantException():
            LinearAlgebraException("The determinant of matrix is zero" ) {}
    }; // class ZeroDeterminantException

    class IndexOutOfRangeException: public LinearAlgebraException {
    public:
        IndexOutOfRangeException(std::size_t i, std::size_t j, 
                                std::size_t n, std::size_t m):
            LinearAlgebraException("Index out of range. Trying to access [" +
                                    std::to_string(i) + "," + std::to_string(j) + 
                                    "] in a " + std::to_string(n) + "x" +
                                    std::to_string(m) + " matrix.") {}

        IndexOutOfRangeException(std::size_t i, std::size_t n):
            LinearAlgebraException("Index out of range. Trying to access [" +
                                    std::to_string(i) + "] in a " + 
                                    std::to_string(n) + "-sized vector.") {}
    }; // class IndexOutOfRangeException

    class IrrationalSpaceUsageException: public LinearAlgebraException {
    public:
        IrrationalSpaceUsageException():
            LinearAlgebraException("The space is being used irrationally" ) {}
    }; // class IrrationalSpaceUsageException

} // namespace linear_algebra

#endif // LINALG_EXCEPTION_HPP