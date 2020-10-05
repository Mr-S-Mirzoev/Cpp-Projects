#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "Dependencies/sequence.hpp"
#include "Dependencies/random.hpp"

#include "swap.hpp"

#include <functional>
#include <iostream>

template <typename T, typename Comparator>
void shellSort_Worker(Lab::Sequence<T> *A, int first, int last, const Comparator &comp) {
    for (int d = (last - first) / 2; d != 0; d /= 2 )
//нужен цикл для first = a[0..d-1]
        for (int i = first + d; i != last; ++i)
            for (int j = i; j - first >= d && comp(A->Get(j), A->Get(j - d)); j -= d)
                swap (A, j, j - d);
}

template <typename T, typename Comparator>
void shellSort(Lab::Sequence<T> *A, const Comparator &c) {
    shellSort_Worker(A, 0, A->GetSize(), c);
}

#endif