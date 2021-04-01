#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "blaze/Math.h"

#include "set.hpp"
#include "loss.hpp"

#include <memory>

constexpr const double LAMBDA_DEFAULT = 0.05;
constexpr const double SPEED_DEFAULT = 0.05;
constexpr const double WTHRESHOLD_DEFAULT = 0.05;
constexpr const double RTHRESHOLD_DEFAULT = 0.05;

class StochasticGradientDescent
{
private:
    blaze::CompressedVector<double, blaze::columnVector> _weights;
    std::shared_ptr <TrainingSet> _set;
    LossFunction _lf;
    double _lambda;
    double _speed;
    double _emperical_risk = 0;
    double _weight_threshold;
    double _emperical_risk_threshold;
public:
    StochasticGradientDescent(
        std::shared_ptr <TrainingSet> &set,
        const LossFunction &loss,
        double l = LAMBDA_DEFAULT,
        double s = SPEED_DEFAULT,
        double weight_threshold = WTHRESHOLD_DEFAULT,
        double emperical_risk_threshold = RTHRESHOLD_DEFAULT
    ); 

    bool one_iteration();
    void optimize();

    blaze::CompressedVector<double, blaze::columnVector> get_weights() const;
};

#endif // OPTIMIZER_HPP 