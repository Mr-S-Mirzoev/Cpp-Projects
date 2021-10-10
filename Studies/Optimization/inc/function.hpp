#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "linear_algebra/matrix.hpp"
#include "exceptions.hpp"

class Function
{
public:
    virtual double value(const linear_algebra::Matrix& point) = 0;
    virtual linear_algebra::Matrix grad(const linear_algebra::Matrix& point) = 0;
    virtual linear_algebra::Matrix hessian(const linear_algebra::Matrix& point) = 0;
};

class Function1: public Function
{
public:

    double value(const linear_algebra::Matrix& point) {
        if (point.m() != 1)
            throw NotAVectorException(point.n(), point.m());

        //  f(x) = x_1^2 + x_2^2 + 2x_3^2 + x_4^2 - 5x_1 - 5x_2 - 21x_3 + 7x_4
        double f_val  = std::pow(point[0], 2.) + std::pow(point[1], 2.) + 
                        2 * std::pow(point[2], 2.) + std::pow(point[3], 2.) -
                        5 * point[0] - 5 * point[1] - 21 * point[2] + 7 * point[3];

        return f_val;
    }

    linear_algebra::Matrix grad(const linear_algebra::Matrix& point) {
        if (point.m() != 1)
            throw NotAVectorException(point.n(), point.m());

        //  f'(x) = { 2 * x_1 - 5 ,  2 * x_2 - 5,  4 * x_3 - 21 ,  2 * x_4 + 7 } 
        linear_algebra::Matrix f_grad(4);
        f_grad[0] = 2 * point[0] - 5;
        f_grad[1] = 2 * point[1] - 5;
        f_grad[2] = 4 * point[2] - 21;
        f_grad[3] = 2 * point[3] + 7;

        return f_grad;
    }

    linear_algebra::Matrix hessian(const linear_algebra::Matrix& point) {
        if (point.m() != 1)
            throw NotAVectorException(point.n(), point.m());

        linear_algebra::Matrix f_hessian(4, 4);

        for (std::size_t i = 0; i < 4; ++i)
            for (std::size_t j = 0; j < 4; ++j)
                if (i == j)
                    if (i == 2)
                        f_hessian[{i, j}] = 4;
                    else
                        f_hessian[{i, j}] = 4;
                else
                    f_hessian[{i, j}] = 0;

        return f_hessian;
    }
};

#endif // FUNCTION_HPP