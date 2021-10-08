#include "newton.hpp"

linear_algebra::Matrix NewtonOptimizer::minimize(std::function<double (const linear_algebra::Matrix &)> f, const linear_algebra::Matrix & start) {
    /* x_new = x − J(x)^−1 * f(x) */
}