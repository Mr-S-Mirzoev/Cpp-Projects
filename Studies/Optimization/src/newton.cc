#include "newton.hpp"

linear_algebra::Matrix NewtonOptimizer::minimize(std::function<double (const linear_algebra::Matrix &)> f, const linear_algebra::Matrix & start) {
    /* x_new = x − f''(x)^−1 * f'(x) */

    {\displaystyle ,\qquad k\geq 0.}

    linear_algebra::Matrix x_new = start - (Jakobian(f, x)^(-1)) * 
}