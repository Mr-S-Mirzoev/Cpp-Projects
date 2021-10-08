#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <cmath>
#include <vector>
#include <optional>

#include "function.hpp"

class BarrierOptimizer {
    double _eps, _fee, _lr, _pow;
    linear_algebra::Matrix _start, _current;
    bool _final = false;
    unsigned _k = 0;
    void iterate(Function *f, std::vector <Function *> gs, std::optional<std::vector <Function *>> hs = std::nullopt);
public:
    BarrierOptimizer(const linear_algebra::Matrix &_start, double _eps, double _fee, double _lr, double _pow);
    void optimize(Function *f, std::vector <Function *> g, std::optional<std::vector <Function *>> h = std::nullopt, unsigned max_k = 40);
};

#endif // BARRIER_HPP