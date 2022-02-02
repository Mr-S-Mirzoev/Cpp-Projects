#include <vector>
#include <iostream>

class Solution {
public:
    int firstMissingPositive(std::vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] <= 0) {
                nums[i] = -1;
            } else if (nums[i] <= nums.size() && nums[i] != i - 1) {
                nums[i] = -1;
                nums[nums[i] - 1] = nums[i];
            }
        }

        for (int i = 0; i < nums.size(); ++i)
            if (nums[i] == -1)
                return i + 1;

        return nums.size() + 1;
    }
};

int main(int argc, char const *argv[])
{
    Solution s;
    std::vector <int> v = {3, 4, -1, 1};
    std::cout << s.firstMissingPositive(v) << std::endl;
    return 0;
}
