#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

long long cost(int leaf0, int leaf1, 
               const std::vector<int> &heap) {
    long long result = 1;
    while (leaf0 != leaf1) {
        if (leaf0 > leaf1) {
            result *= heap[leaf0];
            leaf0 = (leaf0 - 1) / 2;
        } else {
            result *= heap[leaf1];
            leaf1 = (leaf1 - 1) / 2;
        }
    }

    return result * heap[leaf0];
}

int main()
{   
    int N;
    std::cin >> N;
    std::vector<int> _values(N);
    std::vector<int> _idx_in_heap(N);
    std::vector<bool> _has_childs(N);
    std::vector<int> _heap(1);
    for (int i = 0; i < N; ++i) {
        std::cin >> _values[i];
    }

    _idx_in_heap[0] = 0;
    int parent = 0, child;
    _heap[0] = _values[0];
    for (int i = 0; i < N - 1; ++i) {
        int new_parent;
        std::cin >> new_parent >> child;

        _has_childs[new_parent - 1] = true;
        
        int new_idx;
        if (parent == new_parent) {
            new_idx = _idx_in_heap[new_parent - 1] * 2 + 2;
        } else {
            new_idx = _idx_in_heap[new_parent - 1] * 2 + 1;
        }
        
        if (new_idx >= _heap.size()) {
            _heap.resize(new_idx + 1);
        }

        _heap[new_idx] = _values[child - 1];
        _idx_in_heap[child - 1] = new_idx;
        parent = new_parent;
    }

    std::vector <int> _leaves;
    for (int i = 0; i < _has_childs.size(); ++i)
        if (!_has_childs[i])
            _leaves.push_back(i);

    bool not_set = true;
    long long max;
    for (int i = 0; i < _leaves.size(); ++i) {
        for (int j = i + 1; j < _leaves.size(); ++j) {
            int hidx_i = _idx_in_heap[_leaves[i]];
            int hidx_j = _idx_in_heap[_leaves[j]];
            
            long long cst = cost(hidx_i, hidx_j, _heap);

            if (not_set) {
                max = cst;
                not_set = false;
            } else {
                if (cst > max) 
                    max = cst;
            }
        }
    }

    std::cout << max << std::endl;

	return 0;
}