#include <iostream>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    std::vector<double> averageOfLevels(TreeNode* root)
    {
        std::vector<TreeNode*> current_level;
        current_level.push_back(root);

        std::vector<double> averages;
        bool some_not_null = true;
        while (true)
        {
            double sum = 0.;
            unsigned count = 0;
            for (auto node : current_level)
                if (node)
                {
                    ++count;
                    sum += node->val;
                }

            if (!count)
                break;
            averages.push_back(sum / count);

            std::vector<TreeNode*> next_level;

            for (auto node : current_level)
            {
                if (node)
                {
                    next_level.push_back(node->left);
                    next_level.push_back(node->right);
                }
            }

            current_level = std::move(next_level);
        }

        return averages;
    }
};

int main(int argc, char const* argv[])
{
    TreeNode* root = new TreeNode(2);
    root->left = new TreeNode(4);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(-3);
    root->left->right = new TreeNode(11);
    root->right->left = new TreeNode(-34);
    Solution s;
    auto res = s.averageOfLevels(root);
    for (int i = 0; i < res.size(); ++i)
        std::cout << i << ": " << res[i] << std::endl;
    return 0;
}
