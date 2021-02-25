#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class TreeNode {
    TreeNode *parent_;
    std::vector <TreeNode *> childs_;
public:
    TreeNode(TreeNode *parent = nullptr): parent_(parent) {}
    TreeNode* append() {
        auto ptr = new TreeNode(this);
        childs_.push_back(ptr);
        return ptr;
    }

    TreeNode* get_parent() const {
        return parent_;
    }

    void print(int tb = 0) const {
        std::string s(tb, '\t');
        std::cout << s << "(sz=" << childs_.size() << std::endl;
        for (auto child : childs_) {
            child->print(tb + 1);
        }
    }

    int count() const {
        if (childs_.size() == 0) {
            return 1;
        } else {
            int sum = 0;
            for (auto child : childs_) {
                sum += child->count();
            }
            return sum * 2;
        }
    }

    int root_count() const {
        int sum = 0;
        for (auto child : childs_) {
            sum += child->count();
        }
        return sum;
    }
};

void tn_from_string(const std::string &s, int &i, TreeNode *tn) {
    while (i < s.length()) {
        if (s[i] == '(') {
            auto new_tn = tn->append();
            ++i;
            tn_from_string(s, i, new_tn);
        } else {
            ++i;
            return;
        }
    }
}

class Solution {
public:
    int scoreOfParentheses(std::string input) {
        int i = 0;
        auto root = new TreeNode();
        tn_from_string(input, i, root);
        //root->print();
        return root->root_count();
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
