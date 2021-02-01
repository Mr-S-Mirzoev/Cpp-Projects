# Readers and Writers problem

## Problem statement

You need to implement a reader-writer process interaction scheme under Linux using the appropriate Linux Kernel API system calls and multithreading, using threads and muteces. The priority can be any. Threads must share a common address space.

The number of readers, writers, program repeats, and time delays are set by the preprocessor directives.  Ensure that the results of the work of readers and writers are displayed on the screen.


## How to build

    g++ task1.cpp -std=c++11 -o readers-writers
    ./readers-writers
