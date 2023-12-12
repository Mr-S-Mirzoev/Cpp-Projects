#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "Dependencies/random.hpp"
#include "Dependencies/sequence.hpp"
#include "isorter.hpp"
#include "swap.hpp"

#include <functional>
#include <iostream>

template <typename T>
class ShellSorter : public ISorter<T>
{
    void shellSort_Worker(Lab::Sequence<T>* _sequence, int first, int last, int (*cmp)(T, T))
    {
        for (int d = (last - first) / 2; d != 0; d /= 2)
            for (int i = first + d; i != last; ++i)
                for (int j = i;
                     j - first >= d && cmp(_sequence->Get(j), _sequence->Get(j - d)) <= 0; j -= d)
                    swap(_sequence, j, j - d);
    }

public:
    Lab::Sequence<T>* sort(Lab::Sequence<T>* _sequence, int (*cmp)(T, T)) override
    {
        Lab::Sequence<T>* x = _sequence->GetSubSequence(0, _sequence->GetSize());
        shellSort_Worker(x, 0, _sequence->GetSize(), cmp);
        return x;
    }
};

#endif