#ifndef SET_HPP
#define SET_HPP

#include "blaze/Math.h"

class SetObject
{
private:
    blaze::CompressedVector<double, blaze::columnVector> _x;
    double _y;
public:
    SetObject(const blaze::CompressedVector<double, blaze::columnVector> &x, double y);
    SetObject();

    void set_x(const blaze::CompressedVector<double, blaze::columnVector> &x);
    void set_x_i(double x_i, int i);
    void set_y(double y);

    blaze::CompressedVector<double, blaze::columnVector> get_x() const;
    double get_x_i(int i) const;
    double get_y() const;
    
};

class TrainingSet
{
private:
    blaze::CompressedVector<SetObject, blaze::rowVector> _objects;
/*
    class ConstIterator {
        std::vector <SetObject>::const_iterator _current_pose;
    public:
        ConstIterator(std::vector <SetObject>::const_iterator &pose);

        ConstIterator& operator++();
        ConstIterator& operator--();

        bool operator==(const ConstIterator& lhs, const ConstIterator& rhs);

        SetObject operator->();
    };
*/
    using ConstIterator = blaze::CompressedVector<SetObject, blaze::rowVector>::ConstIterator;

public:
    void add_object (SetObject && object);
    
    SetObject get_object_by_idx(int idx) const;
    SetObject get_random_object() const;
    std::size_t get_set_size() const;

    ConstIterator begin() const;
    ConstIterator end() const;
};

#endif // SET_HPP 