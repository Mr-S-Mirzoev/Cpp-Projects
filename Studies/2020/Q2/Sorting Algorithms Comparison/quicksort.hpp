#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Dependencies/random.hpp"
#include "Dependencies/sequence.hpp"
#include "isorter.hpp"
#include "swap.hpp"

#include <functional>
#include <iostream>

/* This function takes last element as pivot,
   places the pivot element at its correct
   position in sorted  array, and places
   all smaller (smaller than pivot) to left
   of pivot and all greater elements to
   right of pivot */
template <typename T> // Compare returns true if a <= b
class QuickSorter : public ISorter<T>
{
    int partition(Lab::Sequence<T>* _sequence, int l, int h, int (*cmp)(T, T))
    {
        T x = _sequence->Get(h);
        int i = l - 1;

        for (int j = l; j <= h - 1; j++)
        {
            if (cmp(_sequence->Get(j), x) <= 0)
            {
                ++i;
                swap(_sequence, i, j);
            }
        }
        swap(_sequence, i + 1, h);
        return (i + 1);
    }

    void quickSort_Worker(Lab::Sequence<T>* a, int l, int h, int (*cmp)(T, T))
    {
        if (l < h)
        {
            /* Partitioning index */
            int p = partition(a, l, h, cmp);
            quickSort_Worker(a, l, p - 1, cmp);
            quickSort_Worker(a, p + 1, h, cmp);
        }
    }

public:
    Lab::Sequence<T>* sort(Lab::Sequence<T>* a, int (*cmp)(T, T)) override
    {
        quickSort_Worker(a, 0, a->GetSize() - 1, cmp);
        return a;
    }
};

#endif