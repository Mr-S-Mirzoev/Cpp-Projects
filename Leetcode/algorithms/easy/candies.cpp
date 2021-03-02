#include <vector>
#include <unordered_set>
#include <iostream>
#include <iterator>

class TimeOptimalSolution {
public:
    int distributeCandies(std::vector<int>& candyType) {
        std::unordered_set <int> unique_types;
        for (auto val : candyType)
            unique_types.insert(val);

        return std::min(candyType.size() / 2, unique_types.size());
    }
};

class MemoryOptimalSolution {
public:
    int distributeCandies(std::vector<int>& candyType) {
        std::vector<int> unique_types;
        for (auto val : candyType) {
            bool found = false;
            for (auto un_val : unique_types) {
                if (val == un_val) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                unique_types.push_back(val);
            }
        }

        return std::min(candyType.size() / 2, unique_types.size());
    }
};

int main(int argc, char const *argv[])
{
    std::vector<int> v(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());
    TimeOptimalSolution s;

    std::cout << "She can eat up to " << s.distributeCandies(v) << " different types of candies" << std::endl;

    return 0;
}
