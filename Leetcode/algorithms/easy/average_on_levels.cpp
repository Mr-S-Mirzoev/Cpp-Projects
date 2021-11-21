#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    std::vector<double> averageOfLevels(TreeNode* root) {
        std::vector <TreeNode*> current_level;
        current_level.push_back(root);
        
        std::vector <double> averages;
        bool some_not_null = true;
        while (true) {
            double sum = 0.;
            unsigned count = 0;
            for (auto node : current_level)
                if (node) {
                    ++count;
                    sum += node->val;
                }

            if (!count)
                break;
            averages.push_back(sum / count);

            std::vector <TreeNode*> next_level;

            for (auto node : current_level) {
                if (node) {
                    next_level.push_back(node->left);
                    next_level.push_back(node->right);
                }
            }

            current_level = std::move(next_level);
        }

        return averages;
    }
};