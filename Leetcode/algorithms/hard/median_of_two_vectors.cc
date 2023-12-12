#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec)
{
    os << "{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os << "}";
    return os;
}

class Solution
{
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int sz1 = nums1.size();
        int sz2 = nums2.size();
        int merge_len = (sz1 + sz2);

        int odd = merge_len % 2;
        bool first = false;

        int head1 = -1;
        int head2 = -1;
        int count = 0;
        int save, current;

        while (count < merge_len / 2 + 1)
        {

            if (head1 == sz1 - 1)
            {
                current = nums2[head2 + 1];
                ++head2;
            }
            else if (head2 == sz2 - 1)
            {
                current = nums1[head1 + 1];
                ++head1;
            }
            else if (nums1[head1 + 1] < nums2[head2 + 1])
            {
                current = nums1[head1 + 1];
                ++head1;
            }
            else
            {
                current = nums2[head2 + 1];
                ++head2;
            }

            if (count == merge_len / 2 - (1 - odd))
            {
                if (odd)
                {
                    return current;
                }
                else
                {
                    save = current;
                }
            }
            else if (count == merge_len / 2)
            {
                return 0.5 * (save + current);
            }

            ++count;
        }
    }
};

int main(int argc, char const* argv[])
{
    Solution s;
    std::vector<int> v1{2};
    std::vector<int> v2{};

    double res = s.findMedianSortedArrays(v1, v2);

    std::cout << "Finding median of sorted arrays: " << std::endl;

    std::cout << "First vector: " << v1 << std::endl;
    std::cout << "Second vector: " << v2 << std::endl;

    std::cout << "Result: " << res << std::endl;
    return 0;
}
