#ifndef INTERFACE_H
#define INTERFACE_H

#include "Dependencies/random.hpp"

#include "test.hpp"
#include "random_sequence.hpp"
#include "quicksort.hpp"
#include "shellsort.hpp"
#include <string>
#include <sstream>

std::vector <std::string> split(const std::string &str) 
{ 
    std::vector <std::string> result;
    // Used to split string around spaces. 
    std::istringstream ss(str); 
  
    // Traverse through all words 
    do { 
        // Read a word 
        std::string word; 
        ss >> word; 
        if (!word.empty())
            result.push_back(word); 
        // While there is more to read 
    } while (ss); 
    return result;
} 

inline void help () {
    std::cout << "1. If you want to test sort correctness:" << std::endl;
    std::cout << "\tStart with \"correct\" to define algo." << std::endl;
    std::cout << "\tThe second argument should be \"shell\" or \"quick\" to define algo." << std::endl;
    std::cout << "\tAfter you should pass \"ascending\", \"descending\" or \"random\"." << std::endl;
    std::cout << "\tThe fourth parameter is whether compare function is:" << std::endl;
    std::cout << "\t\ta) x - y; b) y - x" << std::endl;
    std::cout << "\t\tThe last parameter is optional: \"manual\"" << std::endl;
    std::cout << "2. If you want to test sort time:" << std::endl;
    std::cout << "\tStart with \"time\" to define algo." << std::endl;
    std::cout << "\tThe second argument should be \"shell\" or \"quick\" to define algo." << std::endl;
    std::cout << "\tThe third parameter is \"list\" or \"array\":" << std::endl;
    std::cout << "\tAfter you should pass \"ascending\", \"descending\" or \"random\"." << std::endl;
    std::cout << "\tThe last parameter is whether compare function is:" << std::endl;
    std::cout << "\t\ta) x - y; b) y - x" << std::endl;
    std::cout << "3. If you want to check how fast sequence methods work:" << std::endl;
    std::cout << "\tStart with \"seq-time\" to define function." << std::endl;
    std::cout << "\tThe second argument should be \"list\" or \"array\" to define base of sequence." << std::endl;
    std::cout << "\tAfter you should pass \"get\", \"set\" or \"append\"." << std::endl;
    std::cout << "\nFor help: \"help\". To exit: \"exit\"" << std::endl;
}

void act (const std::string &s) {
    auto splitWords = split(s);
    for (auto word : splitWords) {
        std::cout << word << std::endl;
    }
    switch (splitWords.size()) {
        case 0:
        case 1:
        case 2:
            if (splitWords[0] == "exit")
                exit(0);
            help();
            break;
        case 3:
            if (splitWords[0] == "seq-time") {
                Lab::Sequence<int> *a; 

                if (splitWords[1] =="array")
                    a = new Lab::ArraySequence<int>;
                else if (splitWords[1] =="list")
                    a = new Lab::ListSequence<int>;
                else {
                    help();
                    return;
                }

                int n = getRand(5, 20);
                SetRandomList<int>(a, -20, 20, n);

                SpeedTest *test;
                if (splitWords[2] =="get")
                    test = new GetElementSpeedTest(a);
                else if (splitWords[2] =="set")
                    test = new SetElementSpeedTest(a);
                else if (splitWords[2] =="append")
                    test = new AppendSpeedTest(a);
                else {
                    help();
                    return;
                }
                
                std::cout << "Speed test: " << test->_time << " nanoseconds" << std::endl;
                break;
            } else {
                help();
                return;
            }
            break;
        case 5:
            if (splitWords[0] == "time") {
                ISorter<int> *s;

                if (splitWords[1] =="shell")
                    s = new ShellSorter<int>;
                else if (splitWords[1] =="quick")
                    s = new QuickSorter<int>;
                else {
                    help();
                    return;
                }

                Lab::Sequence<int> *as; 

                if (splitWords[2] =="array")
                    as = new Lab::ArraySequence<int>;
                else if (splitWords[2] =="list")
                    as = new Lab::ListSequence<int>;
                else {
                    help();
                    return;
                }
                int n = getRand(5, 20);
                SetRandomList<int>(as, -20, 20, n);

                if (splitWords[3] =="ascending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return a - b; });
                } else if (splitWords[3] =="descending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return b - a; });
                } else if (splitWords[3] !="random") {
                    help();
                    return;
                }

                if (splitWords[4][0] == 'a') {
                    CheckSortCorrectnessManual csc(s, as, [](int a, int b) { return a - b; });
                    std::cout << std::boolalpha << csc._correct << std::endl;
                } else if (splitWords[4][0] == 'b') {
                    CheckSortCorrectnessManual csc(s, as, [](int a, int b) { return b - a; });
                    std::cout << std::boolalpha << csc._correct << std::endl;
                } else {
                    help();
                    return;
                }
                break;
            } else if (splitWords[0] == "correct") {
                ISorter<int> *s;

                if (splitWords[1] =="shell")
                    s = new ShellSorter<int>;
                else if (splitWords[1] =="quick")
                    s = new QuickSorter<int>;
                else {
                    help();
                    return;
                }

                Lab::Sequence<int> *as = new Lab::ArraySequence<int>;
                int n = getRand(5, 20);
                SetRandomList<int>(as, -20, 20, n);

                if (splitWords[2] =="ascending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return a - b; });
                } else if (splitWords[2] =="descending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return b - a; });
                } else if (splitWords[2] !="random") {
                    help();
                    return;
                }

                if (splitWords[4] == "manual")
                    if (splitWords[3][0] == 'a') {
                        CheckSortCorrectnessManual csc(s, as, [](int a, int b) { return a - b; });
                        std::cout << std::boolalpha << csc._correct << std::endl;
                    } else if (splitWords[3][0] == 'b') {
                        CheckSortCorrectnessManual csc(s, as, [](int a, int b) { return b - a; });
                        std::cout << std::boolalpha << csc._correct << std::endl;
                    } else {
                        help();
                        return;
                    }
                else {
                    help();
                    return;
                }
            }
            break;
        case 4:
            if (splitWords[0] == "correct") {
                ISorter<int> *s;

                if (splitWords[1] =="shell")
                    s = new ShellSorter<int>;
                else if (splitWords[1] =="quick")
                    s = new QuickSorter<int>;
                else {
                    help();
                    return;
                }

                Lab::Sequence<int> *as = new Lab::ArraySequence<int>;
                int n = getRand(5, 20);
                SetRandomList<int>(as, -20, 20, n);

                if (splitWords[2] =="ascending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return a - b; });
                } else if (splitWords[2] =="descending") {
                    QuickSorter<int> sorter;
                    as = sorter.sort(as, [](int a, int b) { return b - a; });
                } else if (splitWords[2] !="random") {
                    help();
                    return;
                }

                if (splitWords[3][0] == 'a') {
                    CheckSortCorrectness csc(s, as, [](int a, int b) { return a - b; });
                    std::cout << std::boolalpha << csc._correct << std::endl;
                } else if (splitWords[3][0] == 'b') {
                    CheckSortCorrectness csc(s, as, [](int a, int b) { return b - a; });
                    std::cout << std::boolalpha << csc._correct << std::endl;
                } else {
                    help();
                    return;
                }
            } else {
                help();
                return;
            }
            break;
        default:
            help();
            return;
    }
}

#endif