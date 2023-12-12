#include <iostream>
#include <unordered_map>
#include <vector>

struct Dependancy
{
    std::vector<char> children;
    bool executed;
};

// set <char, Dependancy *>

void execute_recursive(std::unordered_map<char, Dependancy>& deps_flagged, char start)
{
    for (char child : deps_flagged[start].children)
    {
        if (!deps_flagged[child].executed)
        {
            execute_recursive(deps_flagged, child);
        }
    }

    deps_flagged[start].executed = true;
    std::cout << start << std::endl;
}

void print_deps(std::unordered_map<char, std::vector<char>> const& deps_graph)
{
    std::unordered_map<char, Dependancy> deps_graph_with_flags;
    for (auto& el : deps_graph)
        deps_graph_with_flags[el.first] = {el.second, false};

    for (auto it = deps_graph_with_flags.begin(); it != deps_graph_with_flags.end(); ++it)
    {
        if (!it->second.executed)
        {
            execute_recursive(deps_graph_with_flags, it->first);
        }
    }
}

int main(int argc, char const* argv[])
{
    std::unordered_map<char, std::vector<char>> deps_graph;
    /**
     * A: B, C
     * B: C, D
     * C: D
     * D: -
     **/
    deps_graph['A'] = {'B', 'C'};
    deps_graph['B'] = {'C', 'D'};
    deps_graph['C'] = {'D'};
    deps_graph['D'] = {};
    print_deps(deps_graph);
    return 0;
}
