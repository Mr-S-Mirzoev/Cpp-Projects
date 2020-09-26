#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <benchmark/benchmark.h>
/*
static void BM_ParallelOnProcCount(benchmark::State& state) {
    const auto processor_count = std::thread::hardware_concurrency();
    for (auto _ : state) {
state.PauseTiming();
        Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
state.ResumeTiming();  
        auto c = Matrix<int>::multiply(a, b, processor_count);
    }
}
BENCHMARK(BM_ParallelOnProcCount)->Iterations(1000000);

static void BM_ParallelOnProcCountPlusOne(benchmark::State& state) {
    const auto processor_count = std::thread::hardware_concurrency();
    for (auto _ : state) {
state.PauseTiming();
        Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
state.ResumeTiming();  
        auto c = Matrix<int>::multiply(a, b, processor_count + 1);
    }
}
BENCHMARK(BM_ParallelOnProcCountPlusOne)->Iterations(1000000);

static void BM_Normal(benchmark::State& state) {
    for (auto _ : state) {
state.PauseTiming();
        Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
state.ResumeTiming();  
        auto c = Matrix<int>::multiply(a, b, 0);
    }
}
BENCHMARK(BM_Normal)->Iterations(1000000);
*/

static void BM_ParallelOnOneThread(benchmark::State& state) {
    for (auto _ : state) {
state.PauseTiming();
        Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
state.ResumeTiming();  
        auto c = Matrix<int>::multiply(a, b, 1);
    }
}
BENCHMARK(BM_ParallelOnOneThread)->Iterations(1000000);

static void BM_ParallelOnTwoThreads(benchmark::State& state) {
    for (auto _ : state) {
state.PauseTiming();
        Matrix <int> a(3, 4, true, -20, 20), b(4, 5, true, -20, 20);
state.ResumeTiming();  
        auto c = Matrix<int>::multiply(a, b, 2);
    }
}
BENCHMARK(BM_ParallelOnTwoThreads)->Iterations(1000000);

BENCHMARK_MAIN();