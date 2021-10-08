#ifndef NEWTON_HPP
#define NEWTON_HPP

#include "linear_algebra/matrix.hpp"
#include <functional>

class NewtonOptimizer
{
    /* data */
public:
    NewtonOptimizer(/* args */);
    linear_algebra::Matrix minimize(std::function<double (const linear_algebra::Matrix &)> f, const linear_algebra::Matrix & start);
};


#endif // NEWTON_HPP