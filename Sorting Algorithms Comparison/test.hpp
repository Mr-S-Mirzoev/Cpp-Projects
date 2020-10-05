#include "timer.hpp"
#include "quicksort.hpp"
#include "shellsort.hpp"

// classes which support RAII strategy.

struct Test {};

struct SpeedTest: public Test {
    int64_t _time1;
    int64_t _time2;
};

struct CorrectnessTest: public Test {
    bool _correct = true;
};

template <class Comparator, class Sorter>
struct CheckSortCorrectness: public CorrectnessTest {
    CheckSortCorrectness(Lab::Sequence<int> *a, const Comparator &cmp, const Sorter &s) {
        s(a, cmp);
        int size = a->GetSize();
        for (int i = 1; i < size; ++i)
            if (!cmp(a->Get(i - 1), a->Get(i)) && cmp(a->Get(i), a->Get(i - 1)))
                _correct = false;
    }
};

// Doesn't follow RAII as dealing with I/O in class constructor is bad.
template <class Comparator, class Sorter>
class CheckSortCorrectnessManual: public CorrectnessTest {
    Lab::Sequence<int> *_a;
    const Comparator &_cmp;
    const Sorter &_sort;
public:
    CheckSortCorrectnessManual( 
        Lab::Sequence<int> *a, 
        const Comparator &cmp, 
        const Sorter &s):
        _a(a), _cmp(cmp), _sort(s) {}
    bool check() {
        _a->Print();
        _sort(_a, _cmp);
        _a->Print();

        std::cout << "Is it sorted? (yes/no)" << std::endl;
        std::string s;
        std::cin >> s;

        while (s != "yes" && s != "no") {
            std::cout << "You've entered the wrong value." <<
                        " Try again with \"yes\" or \"no\"" << std::endl;
            std::cin >> s;
        }
        _correct = (s == "yes");
    }
};