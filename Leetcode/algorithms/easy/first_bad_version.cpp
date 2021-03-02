// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

#include <iostream>
#include <functional>

class Solution {
    int binSearch (int left, int right) {
        if (left == right)
            return left;
        
        int middle = left + (right - left) / 2;
        int is_middle_bad = isBadVersion(middle);

        if (right - left == 1) {
            return is_middle_bad ? left : right;
        }

        if (is_middle_bad) {
            return binSearch(left, middle);
        } else {
            return binSearch(middle, right);
        }
    }
    int first_;
    bool isBadVersion(int ver) {
        std::cout << "isBadVersion(" << ver << ")" << std::endl;
        return ver >= first_;
    }
public:
    Solution (int first): first_(first) {}

    int firstBadVersion(int n) {
        int left = 1, right = n;
        int middle = left + (right - left) / 2;
        int first_found;
        int is_middle_bad;

        while (1) {
            if (left == right) {
                first_found = left;
                break;
            }

            is_middle_bad = isBadVersion(middle);

            if (right - left == 1) {
                first_found = is_middle_bad ? left : right;
                break;
            }

            if (is_middle_bad) {
                right = middle;
            } else {
                left = middle;
            }

            middle = left + (right - left) / 2;
        }

        return first_found;
    }
};

int main(int argc, char const *argv[])
{
    int n;
    int first;

    std::cin >> n >> first;

    Solution s{first};

    std::cout << s.firstBadVersion(n) << std::endl;

    return 0;
}
