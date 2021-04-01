#ifndef LOSS_HPP
#define LOSS_HPP

#include "blaze/Math.h"

#include "set.hpp"

#include <memory>

class LossFunction
{
private:
    double (*_loss)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);
    blaze::CompressedVector<double, blaze::columnVector> (*_loss_gradient)(blaze::CompressedVector<double, blaze::columnVector>&, const std::shared_ptr<TrainingSet> &);
    blaze::CompressedVector<double, blaze::columnVector> (*_loss_partial_derivative)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);
public:
    LossFunction(
        double (*loss)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &),
        blaze::CompressedVector<double, blaze::columnVector> (*loss_gradient)(blaze::CompressedVector<double, blaze::columnVector>&, const std::shared_ptr<TrainingSet> &),
        blaze::CompressedVector<double, blaze::columnVector> (*loss_partial_derivative)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &) = 0
    );

    double loss(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);

    blaze::CompressedVector<double, blaze::columnVector> d_loss(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &);
    blaze::CompressedVector<double, blaze::columnVector> d_loss(blaze::CompressedVector<double, blaze::columnVector>&, const std::shared_ptr<TrainingSet> &);
};

#endif // LOSS_HPP 