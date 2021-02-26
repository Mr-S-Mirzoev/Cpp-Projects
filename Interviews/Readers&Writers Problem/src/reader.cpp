#include "reader.hpp"
#include "utils.hpp"

#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>

extern unsigned nreaders;
extern unsigned ITER_COUNT;
extern unsigned READERS_SLEEP_TIME_IN_MILLISECONDS;
extern const char *BUFFER_FILE;
extern std::mutex no_writers, no_readers, counter_mutex;

void reader (unsigned id) {
    unsigned prev, current;
    for (unsigned i = 0; i < ITER_COUNT; ++i) {
        no_writers.lock();
            counter_mutex.lock();
                prev = nreaders;
                ++nreaders;
                if (!prev) {
                    no_readers.lock();
                }
            counter_mutex.unlock();
        no_writers.unlock();

        // reading
        std::ifstream in_file(BUFFER_FILE);
        bool empty = false;
        if (!(in_file.is_open())) {
            if (!(is_empty(in_file))) {
                throw std::runtime_error("Unable to open file for reading");
            } else {
                empty = true;
            }
        }
        std::string temp_string;
        if (!empty) {
            getline(in_file, temp_string);
            in_file.close();
            if (temp_string.empty()) {
                temp_string = "File is empty";
            }
        } else {
            temp_string = "File is not created";
        }
        std::cout << "\t\tReader: " + std::to_string(id) + "\tIter " + std::to_string(i) + " Reading: \t" + temp_string + "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(READERS_SLEEP_TIME_IN_MILLISECONDS));

        counter_mutex.lock();
            --nreaders;
            current = nreaders;
            if (!current) {
                no_readers.unlock();
            }
        counter_mutex.unlock();
    }
}