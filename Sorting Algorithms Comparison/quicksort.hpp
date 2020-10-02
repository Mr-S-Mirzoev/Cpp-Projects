#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "Dependencies/sequence.hpp"
#include "Dependencies/random.hpp"
#include <functional>
#include <iostream>

// Function to swap elements in sequence
template <typename T>
void swap(Lab::Sequence<T> *arr, int index_a, int index_b);
  
/* This function takes last element as pivot, 
   places the pivot element at its correct 
   position in sorted  array, and places 
   all smaller (smaller than pivot) to left 
   of pivot and all greater elements to  
   right of pivot */
template <typename T, class Compare> // Compare returns true if a <= b
int partition(Lab::Sequence<T> *arr, int l, int h);
  
/* A[] --> Array to be sorted,  
l --> Starting index,  
h --> Ending index */
template <typename T, class Compare>
void quickSort(Lab::Sequence<T> *arr, int l, int h);

template <typename T>
void SetRandomList(Lab::Sequence<T> *arr, const T& min, const T& max, const int &length);

#endif