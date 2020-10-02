#include "Dependencies/nlohmann/json.hpp"
#include "quicksort.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iomanip>

using json = nlohmann::json;

int main() { /*
    std::system("./mybenchmark --benchmark_format=json --benchmark_out=results.json > /dev/null");
    // read a JSON file
    std::ifstream i("results.json");
    json j;
    i >> j;

    // write prettified JSON to another file
    //std::ofstream o("pretty.json");
    std::cout << std::setw(4) << j["benchmarks"] << std::endl;
    */
    int n = 8; 
    Lab::Sequence<int> *a = new Lab::ArraySequence<int>; 
    SetRandomList<int> (a, -10, 10, n);
    a->Print();
    /*
    SetRandomList<int>(a, -10, 10, n);
    quickSort<int, std::less<int>> (a, 0, n - 1); 
    for (int i = 0; i < n; ++i) { 
        std::cout << a->Get(i) << " "; 
    }*/
    return 0; 
}