# Research

## System info

    Run on (4 X 2300 MHz CPU s)
    CPU Caches:
      L1 Data 32 KiB (x2)
      L1 Instruction 32 KiB (x2)
      L2 Unified 256 KiB (x2)
      L3 Unified 4096 KiB (x1)



## Simple thread pool

First of all I implemented a simple thread pool and it gave me such results on Benchmarking. They were way different from the one I expected... Parallelism was performing worse and in <img src="https://render.githubusercontent.com/render/math?math=1.5 * 10 ^{2}"> times

    2020-09-24T16:23:28+03:00
    Running ./benchmark.out
    Run on (4 X 2300 MHz CPU s)
    CPU Caches:
      L1 Data 32 KiB (x2)
      L1 Instruction 32 KiB (x2)
      L2 Unified 256 KiB (x2)
      L3 Unified 4096 KiB (x1)
    Load Average: 1.29, 1.96, 2.36
    -------------------------------------------------------------------------------------------
    Benchmark                                                 Time             CPU   Iterations
    -------------------------------------------------------------------------------------------
    BM_ParallelOnProcCount/iterations:1000000            346261 ns       164545 ns      1000000
    BM_ParallelOnProcCountPlusOne/iterations:1000000     369152 ns       182542 ns      1000000
    BM_Normal/iterations:1000000                           2501 ns         2364 ns      1000000

## Thread Pool from github

After I used an implemented thread pool from https://github.com/vit-vit/ctpl and it gave me results which were even worse

    2020-09-26T12:20:44+03:00
    Running ./benchmark.out
    Run on (4 X 2300 MHz CPU s)
    CPU Caches:
      L1 Data 32 KiB (x2)
      L1 Instruction 32 KiB (x2)
      L2 Unified 256 KiB (x2)
      L3 Unified 4096 KiB (x1)
    Load Average: 1.56, 1.89, 2.17
    -------------------------------------------------------------------------------------------
    Benchmark                                                 Time             CPU   Iterations
    -------------------------------------------------------------------------------------------
    BM_ParallelOnProcCount/iterations:1000000            332290 ns       204401 ns      1000000
    BM_ParallelOnProcCountPlusOne/iterations:1000000     346535 ns       218863 ns      1000000
    BM_Normal/iterations:1000000                           2228 ns         2217 ns      1000000

## Trying to find the error in logic

1. I got stuck when it came to the situation where I had only 1 and two threads and two threads were working worse than 1

        2020-09-26T12:42:03+03:00
        Running ./benchmark.out
        Run on (4 X 2300 MHz CPU s)
        CPU Caches:
          L1 Data 32 KiB (x2)
          L1 Instruction 32 KiB (x2)
          L2 Unified 256 KiB (x2)
          L3 Unified 4096 KiB (x1)
        Load Average: 1.72, 1.66, 1.99
        -------------------------------------------------------------------------------------
        Benchmark                                           Time             CPU   Iterations
        -------------------------------------------------------------------------------------
        BM_ParallelOnOneThread/iterations:1000000       68690 ns        59237 ns      1000000
        BM_ParallelOnTwoThreads/iterations:1000000     208321 ns       136133 ns      1000000

2. After looking at this [Stack Overflow page](https://stackoverflow.com/questions/52831254/multi-threading-benchmarking-issues) I realised why this happens and decided to change dimensions to the count of 50 by 50. Although result wasn't great again...

        Load Average: 2.28, 2.64, 3.19
        ------------------------------------------------------------------------------------------
        Benchmark                                                Time             CPU   Iterations
        ------------------------------------------------------------------------------------------
        BM_ParallelOnProcCountMinusOne/iterations:10000   61004143 ns     33294763 ns        10000
        BM_ParallelOnProcCount/iterations:10000           61539081 ns     33829332 ns        10000
        BM_Normal/iterations:10000                          411272 ns       410019 ns        10000

3. So I decided to work with a bench of data (roughly splitting all the data between threads at the begining of programm). The formula was as follows: 

        unsigned load = ((c.h / threads_q) > 10) ? 10 : (c.h / threads_q);
        unsigned quantity = (c.h % load) ? unsigned(floor(c.h / load)) + 1 :  unsigned(floor(c.h / load));

  Results now seemed more like fun:) 

    Load Average: 1.81, 1.68, 1.85
    ------------------------------------------------------------------------------------------
    Benchmark                                                Time             CPU   Iterations
    ------------------------------------------------------------------------------------------
    BM_ParallelOnProcCountMinusOne/iterations:10000     268379 ns       119757 ns        10000
    BM_ParallelOnProcCount/iterations:10000             314000 ns       153104 ns        10000
    BM_Normal/iterations:10000                          239863 ns       234943 ns        10000

  Although we were storing info about multiplication of ints, which is quite fast in modern cores. So i decided to go HARDCORE and to make it heaven and hell for programm. Back then dispersion was in (-20, 20). I made it (INT_MIN, INT_MAX) ha-ha. And decided to store it in __int128_t. Here we go))) You're welcome))). Now it's time to find out when will it go tremendous.

    Load Average: 2.01, 1.88, 1.88
    ------------------------------------------------------------------------------------------
    Benchmark                                                Time             CPU   Iterations
    ------------------------------------------------------------------------------------------
    BM_ParallelOnProcCountMinusOne/iterations:10000     648039 ns       153982 ns        10000
    BM_ParallelOnProcCount/iterations:10000             797424 ns       195620 ns        10000
    BM_Normal/iterations:10000                          941707 ns       899438 ns        10000
  
  Here we go))) You're welcome))). Now it's time to find out when will it go tremendous. It looks like here:
  Multiplication of two matrices like that:
  Matrix <__int128_t> a(100, 200, true, INT32_MIN, INT32_MAX), b(200, 120, true, INT32_MIN, INT32_MAX);
  Gave me such result. The key is in the CPU time)

    Load Average: 2.02, 2.12, 1.99
    ------------------------------------------------------------------------------------------
    Benchmark                                                Time             CPU   Iterations
    ------------------------------------------------------------------------------------------
    BM_ParallelOnProcCountMinusOne/iterations:10000    3876667 ns       268726 ns        10000
    BM_ParallelOnProcCount/iterations:10000            4403813 ns       330694 ns        10000
    BM_Normal/iterations:10000                         7538187 ns      7071687 ns        10000


## Optimal No. of threads

  Now I'd like to guess, What is the optimal No of threads compared to No of cores (4 in my case)

    Load Average: 3.34, 2.21, 2.03
    --------------------------------------------------------------------------------
    Benchmark                                      Time             CPU   Iterations
    --------------------------------------------------------------------------------
    BM_ParallelOn1Thread/iterations:10000    6655813 ns       243916 ns        10000
    BM_ParallelOn2Thread/iterations:10000    5955997 ns       337847 ns        10000
    BM_ParallelOn3Thread/iterations:10000   12325268 ns       681494 ns        10000
    BM_ParallelOn4Thread/iterations:10000   11917118 ns       778733 ns        10000
    BM_ParallelOn5Thread/iterations:10000    4065461 ns       355405 ns        10000
  
  Now I'l distinguish 3 best of them and compare with the normal situation (no multithreading).

    Load Average: 1.41, 1.59, 2.65
    --------------------------------------------------------------------------------
    Benchmark                                      Time             CPU   Iterations
    --------------------------------------------------------------------------------
    BM_ParallelOn1Thread/iterations:10000    7373812 ns       252845 ns        10000
    BM_ParallelOn2Thread/iterations:10000    4319347 ns       253829 ns        10000
    BM_ParallelOn5Thread/iterations:10000    4944124 ns       371604 ns        10000
    BM_Normal/iterations:10000               7574115 ns      7207356 ns        10000

  Looks like a deal, 5 threads;)

## Conclusion

It is stupidish to do parallelism on small functions. It's way better and clever to do it when you deal with a bench of them. 
