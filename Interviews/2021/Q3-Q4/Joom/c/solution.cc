#include <unordered_map>
#include <vector>

std::pair <unsigned, unsigned> find_pair(std::vector<int> const& v, int sum) { // O(N)
    std::unordered_map <int, unsigned> values; // memory O(N) 
    for (unsigned i = 0; i < v.size(); ++i) { // O(N)
        auto it = values.find(sum - v[i]); // O(1)
        if (it != values.end()) {
            return {i, it->second};
        } else {
            values[v[i]] = i; // O(1)
        }
    }

    return {-1, -1};
}