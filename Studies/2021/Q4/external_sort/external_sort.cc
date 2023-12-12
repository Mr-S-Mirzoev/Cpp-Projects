#include <algorithm>
#include <iostream>
#include <queue>
#include <stdio.h>
#include <vector>

#include "c_file.h"

unsigned const LINE_MAX_SIZE = 10; // KB
unsigned const RAM_LIMIT = 250;    // KB
unsigned const MAX_VECTOR_SIZE = RAM_LIMIT / LINE_MAX_SIZE;

struct pair_lower : public std::binary_function<std::pair<unsigned, std::string>,
                                                std::pair<unsigned, std::string>, bool>
{
    bool operator()(const std::pair<unsigned, std::string>& __x,
                    const std::pair<unsigned, std::string>& __y) const
    {
        return __x.second > __y.second;
    }
};

int main(void)
{
    C_File f("input.txt", "r", false);
    unsigned supporting_files_quantity = 0;
    bool should_stop = false;

    while (!should_stop)
    {
        unsigned i = 0;
        std::vector<std::string> v_s(MAX_VECTOR_SIZE);
        for (; i < MAX_VECTOR_SIZE; ++i)
        {
            if (!f.readline(v_s[i]))
            {
                should_stop = true;
                break;
            }
        }
        std::sort(v_s.begin(), v_s.begin() + i);

        std::string supporting_files_name =
            "extra" + std::to_string(supporting_files_quantity) + ".txt";

        if (i != 0)
        {
            C_File out(supporting_files_name, "w", false);
            for (unsigned j = 0; j < i; ++j)
                out.writeline(v_s[j]);

            ++supporting_files_quantity;
        }
    }

    std::vector<C_File> sorted_subs(supporting_files_quantity);
    for (unsigned i = 0; i < supporting_files_quantity; ++i)
    {
        std::string supporting_files_name = "extra" + std::to_string(i) + ".txt";
        sorted_subs[i] = std::move(C_File(supporting_files_name, "r"));
    }

    std::string s;
    C_File output("output.txt", "w", false);
    std::priority_queue<std::pair<unsigned, std::string>,
                        std::vector<std::pair<unsigned, std::string>>, pair_lower>
        q;

    bool all_finished = true;
    for (unsigned i = 0; i < supporting_files_quantity; ++i)
    {
        if (!sorted_subs[i].finished())
            all_finished = false;
    }

    if (all_finished)
        return 0;

    for (unsigned i = 0; i < supporting_files_quantity; ++i)
        if (sorted_subs[i].readline(s))
        {
            q.push({i, s});
        }

    while (!all_finished)
    {
        auto v = q.top();
        unsigned last_max_i = v.first;
        output.writeline(v.second);
        q.pop();
        if (sorted_subs[last_max_i].readline(s))
            q.push({last_max_i, s});
        else
        {
            all_finished = true;
            for (unsigned i = 0; i < supporting_files_quantity; ++i)
            {
                if (!sorted_subs[i].finished())
                    all_finished = false;
            }

            if (all_finished)
                return 0;

            for (unsigned i = 0; i < supporting_files_quantity; ++i)
                if (!sorted_subs[i].finished() && sorted_subs[i].readline(s))
                {
                    q.push({i, s});
                    break;
                }
        }

        all_finished = true;
        for (unsigned i = 0; i < supporting_files_quantity; ++i)
        {
            if (!sorted_subs[i].finished())
                all_finished = false;
        }

        if (all_finished)
            return 0;
    }

    return 0;
}