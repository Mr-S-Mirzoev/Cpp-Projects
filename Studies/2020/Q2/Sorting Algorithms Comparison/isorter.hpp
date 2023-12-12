#ifndef ISORTER_H
#define ISORTER_H

#include "Dependencies/sequence.hpp"

template <typename T>
class ISorter
{
public:
    virtual Lab::Sequence<T>* sort(Lab::Sequence<T>* a, int (*cmp)(T, T)) = 0;
};

#endif