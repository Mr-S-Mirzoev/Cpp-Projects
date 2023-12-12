#ifndef RANDOM_SEQUENCE_H
#define RANDOM_SEQUENCE_H

#include "Dependencies/sequence.hpp"

template <typename T>
void SetRandomList(Lab::Sequence<T>* arr, const T& min, const T& max, const int& length)
{
    for (int i = 0; i < length; ++i)
        arr->Append(getRand(min, max));
}

#endif