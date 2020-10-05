.PHONY: clean all benchmark programm install

all: install

filename = sort.cpp
target_binary = sort

install: programm

programm:
	g++ $(filename) -std=c++11 -o $(target_binary)

clean:
	rm -rf *.o *.out $(target_benchmark_binary) $(target_binary)