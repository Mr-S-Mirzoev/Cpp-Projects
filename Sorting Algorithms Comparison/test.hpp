#ifndef TEST_H
#define TEST_H

#include "timer.hpp"
#include "quicksort.hpp"
#include "shellsort.hpp"
#include "Dependencies/random.hpp"
#include "Dependencies/sequence.hpp"

// classes which support RAII strategy.

struct Test {};

struct SpeedTest: public Test {
    int64_t _time;
};

struct CorrectnessTest: public Test {
    bool _correct = true;
};

struct CheckSortCorrectness: public CorrectnessTest {
    CheckSortCorrectness(ISorter<int> *s, Lab::Sequence <int> *sequence, int (*cmp) (int,int)) {
        auto *a = s->sort(sequence, cmp);
        int size = a->GetSize();
        for (int i = 1; i < size; ++i)
            if (cmp(a->Get(i - 1), a->Get(i)) > 0)
                _correct = false;
    }
private:
    ISorter<int> *_sort;
};

// Doesn't follow RAII as dealing with I/O in class constructor is bad.
class CheckSortCorrectnessManual: public CorrectnessTest {
public:
    CheckSortCorrectnessManual(ISorter<int> *s, Lab::Sequence <int> *sequence, int (*cmp) (int,int)) {
        auto *a = s->sort(sequence, cmp);
        a->Print();

        std::cout << "Is it sorted? (yes/no)" << std::endl;
        std::string str;
        std::getline(std::cin, str);

        while (str != "yes" && str != "no") {
            std::cout << "You've entered the wrong value." <<
                        " Try again with \"yes\" or \"no\"" << std::endl;
            std::getline(std::cin, str);
        }
        _correct = (str == "yes"); 
    }
};

struct SortSpeedTest: public SpeedTest {
    SortSpeedTest(ISorter<int> *sorter, Lab::Sequence <int> *sequence, int (*cmp) (int,int)) {
        Timer t;
        sorter->sort(sequence, cmp);
        _time = t.pause();
    }
};

struct GetElementSpeedTest: public SpeedTest {
    GetElementSpeedTest(Lab::Sequence<int> *a) {
        int index = getRand<int>(0, a->GetSize());
        Timer t;
        a->Get(index);
        _time = t.pause();
    }
};

struct SetElementSpeedTest: public SpeedTest {
    SetElementSpeedTest(Lab::Sequence<int> *a) {
        int index = getRand<int>(0, a->GetSize());
        Timer t;
        a->Set(0, index);
        _time = t.pause();
    }
};

struct AppendSpeedTest: public SpeedTest {
    AppendSpeedTest(Lab::Sequence<int> *a) {
        Timer t;
        a->Append(0);
        _time = t.pause();
    }
};

#endif