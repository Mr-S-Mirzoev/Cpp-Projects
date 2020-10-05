#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Dependencies/sequence.hpp"
#include "Dependencies/random.hpp"
#include "swap.hpp"

#include <functional>
#include <iostream>
  
/* This function takes last element as pivot, 
   places the pivot element at its correct 
   position in sorted  array, and places 
   all smaller (smaller than pivot) to left 
   of pivot and all greater elements to  
   right of pivot */
template <typename T, typename Comparator> // Compare returns true if a <= b
int partition(Lab::Sequence<T> *arr, int l, int h, const Comparator &cmp) 
{
    T x = arr->Get(h); 
    int i = l - 1; 
  
    for (int j = l; j <= h - 1; j++) { 
        if (cmp(arr->Get(j), x)) { 
            ++i;
            swap(arr, i, j); 
        } 
    } 
    swap(arr, i + 1, h); 
    return (i + 1); 
} 
  
template <typename T, typename Comparator>
void quickSort_Worker(Lab::Sequence<T> *A, int l, int h, const Comparator &c) 
{
    if (l < h) { 
        /* Partitioning index */
        int p = partition<T, Comparator>(A, l, h, c); 
        quickSort_Worker(A, l, p - 1, c); 
        quickSort_Worker(A, p + 1, h, c); 
    } 
} 

template <typename T, typename Comparator>
void quickSort(Lab::Sequence<T> *A, const Comparator &c) {
    quickSort_Worker(A, 0, A->GetSize() - 1, c);
}

#endif