#include "set.hpp"
#include "random_number_generator.hpp"

SetObject::SetObject(const blaze::CompressedVector<double, blaze::columnVector> &x, double y):
    _x(x), _y(y) {} 



void SetObject::set_x(const blaze::CompressedVector<double, blaze::columnVector> &x) {
    _x = x;
}

void SetObject::set_x_i(double x_i, int i) {
    _x[i] = x_i;
}

void SetObject::set_y(double y) {
    _y = y;
}



blaze::CompressedVector<double, blaze::columnVector> SetObject::get_x() const {
    return _x;
}

double SetObject::get_x_i(int i) const {
    return _x[i];
}

double SetObject::get_y() const {
    return _y;
}



void TrainingSet::add_object (SetObject && object) {
    auto sz = _objects.size();
    _objects.resize(sz + 1);
    _objects[sz] = std::move(object);
}



SetObject TrainingSet::get_object_by_idx(int idx) const {
    return _objects.at(idx);
}

SetObject TrainingSet::get_random_object() const {
    return _objects.at(getRand<int>(0, _objects.size() - 1));
}

std::size_t TrainingSet::get_set_size() const {
    return _objects.size();
}



TrainingSet::ConstIterator TrainingSet::begin() const {
    return _objects.cbegin();
}

TrainingSet::ConstIterator TrainingSet::end() const {
    return _objects.cend();
}