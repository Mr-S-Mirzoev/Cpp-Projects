# Reader-Writer Interaction Scheme

Implement an interaction scheme for the "readers-writers" problem on Linux OS using appropriate UNIX system calls and multi-threading with `thread`, `event`, and `mutex`. The priority can be arbitrary. Threads must share a common address space. The number of readers, writers, program repetitions, as well as time delays, are to be set using preprocessor directives. Ensure that the output of the readers and writers is displayed on the screen.

## How to build

    g++ task1.cpp -std=c++11 -o readers-writers
    ./readers-writers
