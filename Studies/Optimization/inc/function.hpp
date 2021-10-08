#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "linear_algebra/matrix.hpp"
#include "exceptions.hpp"

class Function
{
public:
    double value(const linear_algebra::Matrix& point) = 0;
    linear_algebra::Matrix grad(const linear_algebra::Matrix& point) = 0;
};

class ExactFunction: public Function
{
public:

    double value(const linear_algebra::Matrix& point) {
        if (point.m() != 1)
            throw NotAVectorException(point.n(), point.m());

        /*
        Here should be a formula
        */
    }

    linear_algebra::Matrix grad(const linear_algebra::Matrix& point) {
        if (point.m() != 1)
            throw NotAVectorException(point.n(), point.m());

        /*
        Here should be a formula
        */
    }
};

#endif // FUNCTION_HPP