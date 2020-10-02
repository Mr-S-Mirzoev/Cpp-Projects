.PHONY: clean all benchmark programm install

all: install

filename = sort.cpp
target_binary = sort
benchmark_file = benchmark.cpp
target_benchmark_binary = mybenchmark

install: benchmark programm
	
benchmark:
	g++ $(benchmark_file) -std=c++11 -isystem Dependencies/benchmark/include \
	-LDependencies/benchmark/build/src -lbenchmark -lpthread -o $(target_benchmark_binary)

programm:
	g++ $(filename) quicksort.cpp -std=c++11 -o $(target_binary)

clean:
	rm -rf *.o *.out $(target_benchmark_binary) $(target_binary)