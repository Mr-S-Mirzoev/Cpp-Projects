
#include <chrono>
#include <initializer_list>
#include <inttypes.h>
#include <iostream>
#include <fstream>

#include "filesystem_utils.hpp"
#include "int128_support.hpp"

int main(int argc, char *argv[]) {
    try {
        std::filesystem::path p (argc > 1 ? argv[1] : ".");
        if (!std::filesystem::is_directory(p)) {
            throw std::logic_error("Provided path doesn't name a directory.");
        }
        int depth = (argc > 2 ? std::stol(argv[2]) : 3);
        std::cout << "Walking through: ";
        std::cout << bold_red(canonicalize_file_name(p.native().c_str())) << std::endl;
        __int128_t x = 0;
        long long max = 0;
        long long min = -1;
        std::cout << "###################################################\n"
                     "############### RECURSIVE DIRWALK #################\n"
                     "###################################################" << std::endl;
        for (int i = 0; i < 100; ++i) {
            std::cout << "=============ITERATION #" << i + 1 << "=============" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            recursive_dirwalk(p, 1, depth);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            long long d = duration.count();
            if (min == -1 || min > d) 
                min = d;
            if (d > max)
                max = d;
            x += d;
        }
        std::cout << "################################################\n"
                     "############### LOOPED DIRWALK #################\n"
                     "################################################" << std::endl;
        __int128_t lx = 0;
        long long lmax = 0;
        long long lmin = -1;
        for (int i = 0; i < 100; ++i) {
            std::cout << "=============ITERATION #" << i + 1 << "=============" << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            looped_dirwalk(p, depth);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            long long d = duration.count();
            if (lmin == -1 || lmin > d) 
                lmin = d;
            if (d > lmax)
                lmax = d;
            lx += d;
        }
        std::fstream fout; 
        // opens an existing csv file or creates a new file. 
        fout.open("report.csv", std::ios::out | std::ios::app); 
        fout << p << ", "
             << max << ", "
             << min << ", "
             << x / 100 << ", "
             << lmax << ", "
             << lmin << ", "
             << lx / 100 << ", "
             << "\n"; 
        std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
        std::cout << bold_red("RECURSIVE:") << std::endl;
        std::cout << "Max time taken by function: " << max << " microseconds" << std::endl;
        std::cout << "Min time taken by function: " << min << " microseconds" << std::endl;
        std::cout << "Average time taken by function: " << x / 100 << " microseconds" << std::endl;
        std::cout << bold_red("ITERATIVE:") << std::endl;
        std::cout << "Max time taken by function: " << lmax << " microseconds" << std::endl;
        std::cout << "Min time taken by function: " << lmin << " microseconds" << std::endl;
        std::cout << "Average time taken by function: " << lx / 100 << " microseconds" << std::endl;
    } catch (std::logic_error &e) {
        std::cerr << "Got a logic error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught an unexpected error." << std::endl;
    }
}
