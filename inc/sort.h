#ifndef SORT_H
#define SORT_H

#include <string>

int create_runs(std::string input_name, int TOTAL_MEM);

// Merge runs from run_"$start".txt to run_"$end".txt
// and write it to run_"$location".txt
void merge_runs(int start, int end, int location);

int merge_all_runs(int runs_count, std::string output_name);

#endif // SORT_H