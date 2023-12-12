#include <iostream>
#include <string>

class Solution
{
public:
    bool isMatch(std::string s, std::string p) { return match(s, 0, p, 0); }

private:
    bool match(std::string s, int i, std::string p, int j)
    {
        if (j == p.length()) // if it's the end of pattern, it should be end of string too.
            return i == s.length();

        char cur = p[j]; // current char

        // If next char is '*', match "?*" instead
        if (j < p.length() - 1 && p[j + 1] == '*')
        {
            int k = i;

            // Check any possible prefix in loop
            while (k < s.length() && (cur == '.' || s[k] == cur))
            {

                // KEY: Only with prefix and suffix are both matched
                if (match(s, k + 1, p, j + 2))
                    return true;

                k++;
            }

            // Check empty prefix
            return match(s, i, p, j + 2);
        }

        // Otherwise, check current wildcard or specific char
        if (i < s.length())
            return (cur == '.' || s[i] == cur) && match(s, i + 1, p, j + 1);

        // End of string, impossible to match
        return false;
    }
};

int main(int argc, char const* argv[])
{
    Solution s;
    std::string str = "aa", ptrn = "a";
    std::cout << "Matching string \"" << str << "\" with pattern \"" << ptrn << "\"" << std::endl;
    std::cout << std::boolalpha << s.isMatch(str, ptrn) << std::endl;
    return 0;
}
