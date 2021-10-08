#include "barrier.hpp"
#include "newton.hpp"

void BarrierOptimizer::iterate(Function *f, std::vector <Function *> gs, std::optional<std::vector <Function *>> hs) {
    NewtonOptimizer no;

    _current = no.minimize(
        [&](const linear_algebra::Matrix &x)->double{
            double sum = 0;
            for (auto g_i : gs) {
                sum += std::pow(
                    std::max(.0, -g_i->value(x)),
                    _pow
                );
            }

            if (hs) {
                for (auto h_i : *hs) {
                    sum += std::pow(
                        std::abs(h_i->value(x)),
                        _pow
                    );
                }
            }

            return f->value(x) + sum * _fee;
        },
        _current
    );

    double sum = 0;
    for (auto g_i : gs) {
        sum += std::pow(
            std::max(.0, -g_i->value(_current)),
            _pow
        );
    }

    if (hs) {
        for (auto h_i : *hs) {
            sum += std::pow(
                std::abs(h_i->value(_current)),
                _pow
            );
        }
    }

    if (_fee * sum < _eps) 
        _final = true;
    else
        _fee *= _lr;

    ++_k;
}

void BarrierOptimizer::optimize(Function *f, std::vector <Function *> g, std::optional<std::vector <Function *>> h, unsigned max_k) {
    while (_k < max_k && !_final) {
        iterate(f, g, h);
    }
}