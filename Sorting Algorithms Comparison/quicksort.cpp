#include "quicksort.hpp"

// Function to swap elements in sequence
template <typename T>
void swap(Lab::Sequence<T> *arr, int index_a, int index_b) 
{ 
    T tmp = arr->Get(index_b); // tmp = arr[b]
    arr->Set(arr->Get(index_a), index_b); // arr[b] = arr[a]
    arr->Set(tmp, index_a); // arr[a] = tmp
} 
  
/* This function takes last element as pivot, 
   places the pivot element at its correct 
   position in sorted  array, and places 
   all smaller (smaller than pivot) to left 
   of pivot and all greater elements to  
   right of pivot */
template <typename T, class Compare> // Compare returns true if a <= b
int partition(Lab::Sequence<T> *arr, int l, int h) 
{ 
    T x = arr->Get(h); 
    int i = l - 1; 
  
    for (int j = l; j <= h - 1; j++) { 
        if (Compare(arr->Get(j), x)) { 
            ++i;
            swap(arr, i, j); 
        } 
    } 
    swap(arr, i + 1, h); 
    return (i + 1); 
} 
  
/* A[] --> Array to be sorted,  
l --> Starting index,  
h --> Ending index */
template <typename T, class Compare>
void quickSort(Lab::Sequence<T> *A, int l, int h) 
{ 
    if (l < h) { 
        /* Partitioning index */
        int p = partition(A, l, h); 
        quickSort(A, l, p - 1); 
        quickSort(A, p + 1, h); 
    } 
} 

template <typename T>
void SetRandomList(Lab::Sequence<T> *arr, const T& min, const T& max, const int &length) {
    for (int i = 0; i < length; ++i)
        arr->Append(getRand(min, max));
}
