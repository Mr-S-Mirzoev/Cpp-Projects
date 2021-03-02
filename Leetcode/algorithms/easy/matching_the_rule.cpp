#include <vector>
#include <string>

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