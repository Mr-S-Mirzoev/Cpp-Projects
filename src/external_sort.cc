#include "sort.h"

// KB to B
unsigned long long operator "" _KB(unsigned long long kb) {
    return kb << 10;
}

int main(int argc, char* argv[]) {
    std::string input_name = "input.txt";
    std::string output_name = "output.txt";
    auto TOTAL_MEM = 150_KB;
    
    int runs_count = create_runs(input_name, TOTAL_MEM);

    merge_all_runs(runs_count, output_name);
    return 0;
}