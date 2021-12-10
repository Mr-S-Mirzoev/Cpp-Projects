#include "sort.h"
#include <chrono>
#include <cstring>
#include <iostream>

// KB to B
unsigned long long operator "" _KB(unsigned long long kb) {
    return kb << 10;
}

int main(int argc, char* argv[]) {
    std::string input_name = "input.txt";
    std::string output_name = "output.txt";

    if (const char* env_test_dir = std::getenv("TEST_DIR")) {
        std::string test_dir = env_test_dir;
        input_name = test_dir + "/" + input_name;
        output_name = test_dir + "/" + output_name;
    }

    auto TOTAL_MEM = 150_KB;

    std::cout << "Input file:\t\t" << input_name << std::endl;
    std::cout << "Output file:\t\t" << output_name << std::endl;
    std::cout << "Memory limit:\t\t" << TOTAL_MEM << " bytes" << std::endl;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int runs_count = create_runs(input_name, TOTAL_MEM);
    int ret_val = merge_all_runs(runs_count, output_name);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    if (ret_val) {
        std::cout << "Failed to rename run to " << output_name << ": " << strerror(ret_val) << std::endl;
        return 1;
    }

    std::cout << "Used runs:\t\t" << runs_count << std::endl;
    std::cout << "Sorting took:\t\t" << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs] elapsed time" << std::endl;
    return 0;
}