#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/*
class LeveledString
{
public:
    using level = int;
private:
    std::vector <std::pair<char, level>> data_;
public:
    LeveledString(const std::string &s) {
        level l = 0;
        for (char c : s) {
            if (c == '(') {
                ++l;
            } else {
                --l;
            }
            data_.push_back({c, l});
        }
    }

    std::size_t length() const {
        return data_.size();
    }

    std::pair <char, level> operator [](int i) const {
        return data_[i];
    }
};


class Solution {
public:
    int scoreOfParentheses(std::string S) {
        int i = 0;
        LeveledString ls(S);
        return count(ls, i);
    }

    int count(const LeveledString& s, int &i) {
        int sum = 0;
        LeveledString::level this_level = s[i].second;
        ++i;

        while(i < s.length()) {
            if (s[i - 1].first == '(') {
                if (s[i].first == '(') {
                    sum += count(s, i);
                } else {
                    sum += 1;
                    ++i;
                }
            } else {
                if (s[i].first == '(') {
                    if (s[i].second < this_level) {
                        return sum;
                    } else {
                        sum += count(s, i);
                    }
                } else {
                    return 2 * sum;
                }
            }
        }

        return sum;
    }
};
*/

void replace_all_occurencies(std::string &s, 
                             const std::string &to_replace, 
                             const std::string &replacement) {
    std::size_t spos, replacement_size = to_replace.size();
    while ((spos = s.find(to_replace)) != std::string::npos) {
        s.replace(spos, replacement_size, replacement);
    }
}

class CurrentSolution {
    std::string s_;
    std::vector <int> v_;
public:
    CurrentSolution(const std::string &s): s_(s), v_(s.length()) {
        
    }
};



int main(int argc, char const *argv[])
{
    std::string input;
    std::cin >> input;
    replace_all_occurencies(input, "()", "s");
    if (input.find('(') == std::string::npos) {
        std::cout << std::count(input.begin(), input.end(), 's') << std::endl;
    }
    std::vector<int> v;
    v.erase()
    std::cout << input << std::endl;
    return 0;
}
