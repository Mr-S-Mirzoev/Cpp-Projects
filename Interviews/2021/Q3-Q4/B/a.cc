#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

bool cmp(std::pair<unsigned, unsigned> it1, std::pair<unsigned, unsigned> it2)
{
    return it1.second > it2.second;
}

int main()
{
    std::map<unsigned, unsigned> _value_to_index;
    std::vector<std::pair<unsigned, unsigned>> _frequency;

    int N;
    int val;
    std::cin >> N;
    for (int idx = 0; idx < N; ++idx)
    {
        std::cin >> val;
        std::map<unsigned int, unsigned int>::iterator it = _value_to_index.find(val);

        if (it == _value_to_index.end())
        {
            _value_to_index[val] = _frequency.size();

            std::pair<unsigned, unsigned> to_append;
            to_append.first = val;
            to_append.second = 1;

            _frequency.push_back(to_append);
        }
        else
        {
            ++(_frequency[it->second].second);
        }
    }

    std::stable_sort(_frequency.begin(), _frequency.end(), cmp);
    for (std::vector<std::pair<unsigned int, unsigned int>>::iterator it = _frequency.begin();
         it != _frequency.end(); ++it)
    {
        for (unsigned i = 0; i < it->second; ++i)
            std::cout << it->first << ' ';
    }
    std::cout << std::endl;

    return 0;
}
