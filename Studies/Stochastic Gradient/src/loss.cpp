#include "loss.hpp"
#include "exceptions.hpp"

LossFunction::LossFunction(
    double (*loss)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &),
    blaze::CompressedVector<double, blaze::columnVector> (*loss_gradient)(blaze::CompressedVector<double, blaze::columnVector>&, const std::shared_ptr<TrainingSet> &),
    blaze::CompressedVector<double, blaze::columnVector> (*loss_partial_derivative)(blaze::CompressedVector<double, blaze::columnVector>&, const SetObject &)
): _loss(loss), _loss_gradient(loss_gradient), _loss_partial_derivative(loss_partial_derivative) {}

double LossFunction::loss(blaze::CompressedVector<double, blaze::columnVector>& weights, const SetObject& object) {
    return _loss(weights, object);
}

blaze::CompressedVector<double, blaze::columnVector> LossFunction::d_loss(blaze::CompressedVector<double, blaze::columnVector>& weights, const SetObject& object) {
    if (_loss_partial_derivative)
        return _loss_partial_derivative(weights, object);
    else 
        throw utils::NotImplementedFunctionException("loss_partial_derivative");
}

blaze::CompressedVector<double, blaze::columnVector> LossFunction::d_loss(blaze::CompressedVector<double, blaze::columnVector>& weights, const std::shared_ptr<TrainingSet> &set) {
    return _loss_gradient(weights, set);
} 