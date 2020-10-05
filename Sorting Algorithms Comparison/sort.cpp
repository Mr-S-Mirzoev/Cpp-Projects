#include "Dependencies/random.hpp"

#include "quicksort.hpp"
#include "random_sequence.hpp"
#include "shellsort.hpp"
#include "timer.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
    int n = getRand(5, 20);
    Lab::Sequence<int> *a = new Lab::ArraySequence<int>; 
    SetRandomList<int>(a, -20.0, 20.0, n);
    Timer t;
    shellSort(a, std::greater<int>());
    std::cout << t.pause() << std::endl;
    t.reset();
    a->Print();
    std::cout << t.pause() << std::endl;
    return 0; 
}