#include <iostream>
#include <string>

int count_all(const std::string &s, int &i) {
    int sum = 0;
    int count = 0;
    while (i < s.length()) {
        if (s[i] == '(') {
            ++count;
            ++i;
            sum += count_all(s, i);
        } else {
            ++i;
            
            if (count == 0)
                return 1;
            else
                return sum * 2;
        }
    }

    if (count == 0)
        return 1;
    else
        return sum * 2;
}

int root_count_all(const std::string &s, int &i) {
    int sum = 0;
    while (i < s.length()) {
        if (s[i] == '(') {
            ++i;
            sum += count_all(s, i);
        } else {
            ++i;
            return sum;
        }
    }
    return sum;
}

class Solution {
public:
    int scoreOfParentheses(std::string input) {
        int i = 0;
        return root_count_all(input, i);
    }
};

int main(int argc, char const *argv[])
{
    std::string input;
    std::cin >> input;
    Solution s;
    std::cout << s.scoreOfParentheses(input) << std::endl;
    
    return 0;
}
