#include "Dependencies/random.hpp"

#include "interface.hpp"
#include "quicksort.hpp"
#include "random_sequence.hpp"
#include "shellsort.hpp"
#include "test.hpp"
#include "timer.hpp"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
    /*
    int n = getRand(5, 20);
    Lab::Sequence<int> *a = new Lab::ArraySequence<int>;
    SetRandomList<int>(a, -20, 20, n);
    std::string s;
    std::cin >> s;
    std::cout << s << std::endl;
    ISorter<int> *ss = new ShellSorter<int>;
    CheckSortCorrectnessManual csc(ss, a, [](int x, int y) { return (x - y); });
    csc.check();
    std::cout << (csc._correct ? "true" : "false") << std::endl;
    */
    std::string line;
    while (std::getline(std::cin, line))
    {
        act(line);
    }
    return 0;
}