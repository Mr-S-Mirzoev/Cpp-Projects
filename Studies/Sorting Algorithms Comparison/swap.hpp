#ifndef SWAP_H
#define SWAP_H

#include "Dependencies/sequence.hpp"

// Function to swap elements in sequence
template <typename T>
void swap(Lab::Sequence<T> *arr, int index_a, int index_b) 
{ 
    T tmp = arr->Get(index_b); // tmp = arr[b]
    arr->Set(arr->Get(index_a), index_b); // arr[b] = arr[a]
    arr->Set(tmp, index_a); // arr[a] = tmp
} 

#endif