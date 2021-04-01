#include "optimizer.hpp"

StochasticGradientDescent::StochasticGradientDescent(
    std::shared_ptr <TrainingSet> &set,
    const LossFunction &loss,
    double l,
    double s,
    double weight_threshold,
    double emperical_risk_threshold
):  _set(set),
    _lf(loss),
    _lambda(l),
    _speed(s),
    _weight_threshold(weight_threshold),
    _emperical_risk_threshold(emperical_risk_threshold) {

    blaze::setNumThreads(8);
    
    // Initialize weights

    _weights.assign(blaze::CompressedVector<double, blaze::columnVector>(_weights.size(), .0));

    // Initialize emperical_risk approx.

    _emperical_risk = .0;
    auto set_size = _set->get_set_size();

    for (auto &object : *(_set.get())) {
        double current_loss = _lf.loss(
            _weights, 
            object.value()
        );

        _emperical_risk += current_loss / set_size;
    }

}

bool StochasticGradientDescent::one_iteration() {
    auto random_object = _set->get_random_object();

    double current_loss = _lf.loss(
        _weights, 
        random_object
    );
    
    auto d_weights = _lf.d_loss(_weights, random_object) * _speed;
    _weights -= d_weights;

    auto d_emperical_risk = _lambda * current_loss + (1. - _lambda) * _emperical_risk;
    _emperical_risk = d_emperical_risk;

    return (blaze::max(d_weights) < _weight_threshold || d_emperical_risk < _emperical_risk_threshold);
}

void StochasticGradientDescent::optimize() {
    while (one_iteration()) {}
}

blaze::CompressedVector<double, blaze::columnVector> StochasticGradientDescent::get_weights() const {
    return _weights;
}