#include "matrix.h"
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <ctime>

static void BM_ParallelOn1Thread(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Matrix<__int128_t> a(100, 200, true, INT32_MIN, INT32_MAX),
            b(200, 120, true, INT32_MIN, INT32_MAX);
        state.ResumeTiming();
        auto c = Matrix<__int128_t>::multiply(a, b, 1);
    }
}
BENCHMARK(BM_ParallelOn1Thread)->Iterations(10000);

static void BM_ParallelOn2Thread(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Matrix<__int128_t> a(100, 200, true, INT32_MIN, INT32_MAX),
            b(200, 120, true, INT32_MIN, INT32_MAX);
        state.ResumeTiming();
        auto c = Matrix<__int128_t>::multiply(a, b, 2);
    }
}
BENCHMARK(BM_ParallelOn2Thread)->Iterations(10000);

static void BM_ParallelOn5Thread(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Matrix<__int128_t> a(100, 200, true, INT32_MIN, INT32_MAX),
            b(200, 120, true, INT32_MIN, INT32_MAX);
        state.ResumeTiming();
        auto c = Matrix<__int128_t>::multiply(a, b, 5);
    }
}
BENCHMARK(BM_ParallelOn5Thread)->Iterations(10000);

static void BM_Normal(benchmark::State& state)
{
    for (auto _ : state)
    {
        state.PauseTiming();
        Matrix<__int128_t> a(100, 200, true, INT32_MIN, INT32_MAX),
            b(200, 120, true, INT32_MIN, INT32_MAX);
        state.ResumeTiming();
        auto c = Matrix<__int128_t>::multiply(a, b, 0);
    }
}
BENCHMARK(BM_Normal)->Iterations(10000);

BENCHMARK_MAIN();