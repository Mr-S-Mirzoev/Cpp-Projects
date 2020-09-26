# Strange results from microbenchmarking with futures...

## First of all I implemented a simple thread pool and it gave me such results on Benchmarking:

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

## After I used an implemented thread pool from https://github.com/vit-vit/ctpl and it gave me results which were even worse

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

## But I got stuck when it came to the situation where I had only 1 and two threads and two threads were working worse than 1

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