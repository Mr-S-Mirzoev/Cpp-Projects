#include <iostream>
#include <mutex>
#include <thread>
#include <random>
#include <string>
#include <fstream>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <csignal>

#include "reader.hpp"
#include "utils.hpp"
#include "writer.hpp"

static unsigned ITER_COUNT = 10U;
static unsigned WRITERS_SLEEP_TIME_IN_MILLISECONDS = 200U;
static unsigned READERS_SLEEP_TIME_IN_MILLISECONDS = 1000U;

constexpr unsigned READERS_COUNT = 10U;
constexpr unsigned WRITERS_COUNT = 5U;
constexpr const char *BUFFER_FILE = "buffer.txt";

std::mutex no_writers, no_readers, counter_mutex;
unsigned nreaders = 0;

static void signalHandler( int signum ) {
    std::cout << "Interrupt signal (" + std::to_string(signum) + ") received.\n";

    std::remove (BUFFER_FILE);

    exit(signum);  
}

int main () 
{
    signal(SIGINT, signalHandler); 
    std::vector <std::thread> threads;
    unsigned readers = READERS_COUNT, writers = WRITERS_COUNT;
    
    for (unsigned j = 0; j < READERS_COUNT + WRITERS_COUNT; ++j) {
        if (readers == 0) {
            --writers;
            threads.push_back(std::thread(writer, j));
        } else if (writers == 0) {
            --readers;
            threads.push_back(std::thread(reader, j));
        } else {
            if (intRand(0, 1) == 0) {
                --writers;
                threads.push_back(std::thread(writer, j));
            } else {
                --readers;
                threads.push_back(std::thread(reader, j));
            }
        }
    }
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }
    readers = READERS_COUNT;
    writers = WRITERS_COUNT;

    std::remove (BUFFER_FILE);
    exit(0);
}