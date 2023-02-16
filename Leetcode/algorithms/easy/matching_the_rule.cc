#include <vector>
#include <string>
#include <iostream>

#define THROW_EXCEPTION_IN_ASSIGNMENT []() {std::__throw_runtime_error("Unknown ruleKey"); return -1;} ()

class Solution {
public:
    int countMatches(std::vector<std::vector<std::string>>& items, std::string ruleKey, std::string ruleValue) {
        int index = (ruleKey == "type")  ? 0 : 
                    (ruleKey == "color") ? 1 :
                    (ruleKey == "name")  ? 2 : THROW_EXCEPTION_IN_ASSIGNMENT;

        unsigned count = 0;

        for (auto item : items)
            if (item[index] == ruleValue)
                ++count;

        return count;
    }
};

int main(int argc, char const *argv[])
{
    std::vector<std::vector<std::string>> items = {{"phone","blue","pixel"},{"computer","silver","lenovo"},{"phone","gold","iphone"}};
    std::string ruleKey = "color", ruleValue = "silver";
    Solution s;
    std::cout << s.countMatches(items, ruleKey, ruleValue) << std::endl;
    return 0;
}
