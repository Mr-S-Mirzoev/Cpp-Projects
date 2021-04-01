#include "classification/loss.hpp"

namespace classification {
    double loss(blaze::CompressedVector<double, blaze::columnVector> &weights, const SetObject &object) 
    {
        return blaze::pow2(blaze::trans(object.get_x()) * weights - object.get_y());
    }

    blaze::CompressedVector<double, blaze::columnVector> loss_gradient(
        blaze::CompressedVector<double, blaze::columnVector> &weights, 
        const std::shared_ptr<TrainingSet> &set) 
    {
        double scale = 0;
        auto size = set->get_set_size();

        for (auto it = set->begin(); it != set->end(); ++it) {
            scale += (blaze::trans(it->get_x()) * weights - it->get_y()) * 2.0 / size;
        }        

        return weights * scale;
    }
    
    blaze::CompressedVector<double, blaze::columnVector> loss_partial_derivative(blaze::CompressedVector<double, blaze::columnVector> &weights, const SetObject &object) 
    {
        return weights * ((blaze::trans(object.get_x()) * weights - object.get_y()) * 2.0);
    }
} 