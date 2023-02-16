#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <random>

class Solution {
    std::vector<int> nums_;
    std::vector<int> shuffled_nums_;
public:
    Solution(std::vector<int>& nums): nums_(nums) {}
    
    /** Resets the array to its original configuration and return it. */
    std::vector<int> reset() {
        return nums_;
    }
    
    /** Returns a random shuffling of the array. */
    std::vector<int> shuffle() {
        auto rng = std::default_random_engine {};
        rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
        
        shuffled_nums_ = nums_;
        
        std::shuffle(
            std::begin(shuffled_nums_), 
            std::end(shuffled_nums_), 
            rng
        );

        return shuffled_nums_;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<int> v(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());
    Solution s(v);
    
    std::cout << "Read array: ";
    for (auto u : v) {
        std::cout << u << " ";
    }
    std::cout << std::endl;
    
    auto r = s.reset();
    std::cout << "Reseted array: ";
    for (auto u : r) {
        std::cout << u << " ";
    }
    std::cout << std::endl;

    r = s.shuffle();
    std::cout << "Shuffled array: ";
    for (auto u : r) {
        std::cout << u << " ";
    }
    std::cout << std::endl;

    r = s.reset();
    std::cout << "Reseted array: ";
    for (auto u : r) {
        std::cout << u << " ";
    }
    std::cout << std::endl;

    return 0;
}


/*
struct AdjustXY {
            std_msgs::msg::Header header;

            sequence<int32> x;
            sequence<int32> y;
        };
    };
};
*/