#include <iostream>
#include <iterator>
#include <vector>

class Solution
{
public:
    int findUnsortedSubarray(std::vector<int>& nums)
    {
        int sz = nums.size();
        int max = nums[0], min = nums[sz - 1];
        int left_break = -1, right_break = -1;

        for (int i = 0; i < sz; ++i)
        {
            if (nums[i] < max)
                right_break = i;
            else
                max = nums[i];

            if (nums[sz - i - 1] > min)
                left_break = i;
            else
                min = nums[sz - i - 1];
        }

        return std::max(0, left_break + right_break - sz + 2);
        // right_break - (sz - 1 - left_break) - 1
    }
};

int main(int argc, char const* argv[])
{
    std::vector<int> v(std::istream_iterator<int>(std::cin), std::istream_iterator<int>());
    Solution s;
    for (auto u : v)
    {
        std::cout << u << " ";
    }
    std::cout << std::endl << s.findUnsortedSubarray(v) << std::endl;
    return 0;
}
