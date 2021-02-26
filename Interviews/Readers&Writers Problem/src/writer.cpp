#include "writer.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

extern unsigned ITER_COUNT;
extern unsigned WRITERS_SLEEP_TIME_IN_MILLISECONDS;
extern char *BUFFER_FILE;
extern std::mutex no_writers, no_readers;

void writer (unsigned id) {
    for (unsigned i = 0; i < ITER_COUNT; ++i) {
        no_writers.lock();
            no_readers.lock();
        no_writers.unlock();
        
        // writing
        std::ofstream out_file(BUFFER_FILE);
        if (!(out_file)) {
            throw std::runtime_error("Unable to open file for writing");
        }
        std::cout << "Writer: " + std::to_string(id) + " Iter: " + std::to_string(i) + " is writing\n";
        out_file << currentDateTime() << std::flush;
        out_file.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(WRITERS_SLEEP_TIME_IN_MILLISECONDS));

        no_readers.unlock();
    }
}