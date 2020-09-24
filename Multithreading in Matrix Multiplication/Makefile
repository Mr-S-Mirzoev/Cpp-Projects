all: test

bench_flags = -std=c++11 -lbenchmark -lpthread -O3

test:
	g++ main.cpp -std=c++11 -lpthread -o test.out

benchmark:
	g++ benchmark.cc $(bench_flags) -o benchmark.out

clean:
	rm -rf *.o *.out