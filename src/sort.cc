#include <algorithm>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#include "c_file.h"

class LineFromRun {
    std::string line_;
    unsigned run_id_;
public:
    LineFromRun(std::string line, int run_id): 
        line_(line), run_id_(run_id) {}

    bool operator<(const LineFromRun& rhs) const {
        return (line_.compare(rhs.line_) > 0);
    }

    std::string get_line() const {
        return line_;
    }

    int get_run_id() const {
        return run_id_;
    }
};

int create_runs(std::string input_name, int prog_mem) {
    C_File input(input_name.c_str(), "r");

    int run_count = 0;
    int total_mem_so_far = 0;

    std::vector<std::string> data; 
    // In case of we had junk in data due to optimization techniques.
    data.clear();

    while (!input.finished()) {
        std::string line;
        input.readline(line);

        if (total_mem_so_far + line.size() < prog_mem) {
            // If we haven't reached the RAM - vulneruble space size,
            // add line to vector
            total_mem_so_far += line.size() + 1;

            // Yes, push_back is a time consuming operation,
            // but since we never know how many lines will
            // fit into memory, it's the only thing we can do.
            data.push_back(line);
        } else {
            // Since we've checked that we didn't exceed RAM - vulneruble space, 
            // We can sort the vector. Note that since std::sort (underlying TimSort)
            // May use extra N >> 1 memory, do not set RAM - vulneruble space
            // size too close to the real RAM size.
            sort(data.begin(), data.end());

            ++run_count;
            std::stringstream ss;
            ss << "run_" << run_count << ".txt";
            C_File output(ss.str(), "w");

            int data_size = data.size();
            for (int i = 0; i < data_size; ++i)
                output.writeline(data[i], i != data_size - 1);

            // `line` is already read so we'll start over
            // again, starting with it
            data.clear();
            total_mem_so_far = line.size();
            data.push_back(line);
        }
    }

    // If anything left to be sorted and printed but
    // we exited the loop because of EOF
    if (data.size()) {
        sort(data.begin(), data.end());

        run_count++;
        std::stringstream ss;
        ss << "run_" << run_count << ".txt";
        C_File output(ss.str(), "w");

        int data_size = data.size();
        for (int i = 0; i < data_size; ++i)
            output.writeline(data[i], i != data_size - 1);
    }

    // By the end of this function we have run_count
    // of sorted files which represent subarrays from
    // the input file
    return run_count;
}

// Merge runs from run_"$start".txt to run_"$end".txt
// and write it to run_"$location".txt
void merge_runs(int start, int end, int location) {

    int runs_count = end - start + 1;

    std::vector<C_File> input(runs_count);
    for (int i = 0; i < runs_count; i++) {
        std::stringstream ss;
        ss << "run_" << start + i << ".txt";
        input[i] = std::move(C_File(ss.str(), "r"));
    }

    std::priority_queue<LineFromRun, std::vector<LineFromRun>> heap;

    std::stringstream ss;
    ss << "run_" << location << ".txt";
    C_File output(ss.str(), "w");

    // Form the heap from the first lines of all
    // sorted runs
    for (int i = 0; i < runs_count; i++) {
        std::string line;

        if (!input[i].finished()) {
            input[i].readline(line);
            heap.push(LineFromRun(line, i));
        }
    }

    while (!heap.empty()) {
        // Get the min line from runs
        std::string line = heap.top().get_line(); 
        unsigned run_id = heap.top().get_run_id();
        heap.pop();

        output.writeline(line);
        
        // If the run from which we extracted the string 
        // isn't done, read from it again, otherwise it
        // will suffer and the order will be broken
        if (!input[run_id].finished()) {
            input[run_id].readline(line);
            heap.push(LineFromRun(line, run_id));
        }
    }
}

void merge_all_runs(int runs_count, std::string output_name) {
    int start = 1;
    int end = runs_count;

    while (start < end) {
        int location = end;
        int distance = 100;
        // Upper bound of (end - start + 1) / distance 
        // [Tops of quantity of portions by 100]
        // The runs will be merge this many times
        int merge_count = (end - start + 1) / distance + 1;

        // If the distance of splitting by those portions
        // is actually lower than 100 (usually the case),
        // update the distance to the new value
        if ((end - start + 1) / merge_count < distance)
            distance = (end - start + 1) / merge_count + 1;

        // Iterating merge_count times
        while (start <= end) {
            // merge no more than distance runs a time
            int cur_end = std::min(start + distance, end);

            // merge runs and put the output to the end + 1
            ++location;
            merge_runs(start, cur_end, location);
            start = cur_end + 1;
        }

        // We'll start merging again from the last output file
        end = location;
    }

    std::stringstream ss;
    ss << "run_" << start << ".txt";
    rename(ss.str().c_str(), output_name.c_str());

    // Clean up the directory
    for (int i = 1; i < end; i++) {
        std::stringstream ss;
        ss << "run_" << i << ".txt";
        remove(ss.str().c_str());
    }
}
