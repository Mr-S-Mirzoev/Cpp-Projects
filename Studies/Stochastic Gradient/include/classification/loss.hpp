#ifndef CLASSIFICATION_LOSS_HPP
#define CLASSIFICATION_LOSS_HPP

#include "blaze/Math.h"

#include "set.hpp"

#include <memory>

namespace classification {
    double loss(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);
    blaze::CompressedVector<double, blaze::columnVector> loss_gradient(blaze::CompressedVector<double, blaze::columnVector>&, const std::shared_ptr<TrainingSet> &);
    blaze::CompressedVector<double, blaze::columnVector> loss_partial_derivative(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);
}

#endif // CLASSIFICATION_LOSS_HPP 