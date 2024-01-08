#include <iostream>
#include <limits>

struct NodeTree
{
    int value;

    NodeTree* left = nullptr;
    NodeTree* right = nullptr;
};

bool is_valid_bin_tree(NodeTree* root, int min = std::numeric_limits<int>::min(),
                       int max = std::numeric_limits<int>::max())
{
    if (!root)
        return true;

    if (root->value >= max || root->value <= min)
        return false;

    return is_valid_bin_tree(root->left, min, std::min(root->value, max)) &&
           is_valid_bin_tree(root->right, std::max(root->value, min), max);
}

//          5
//     2         7
//   1  3      6   8

int main()
{
    NodeTree* root = new NodeTree{5};
    root->left = new NodeTree{2};
    root->right = new NodeTree{7};
    root->left->left = new NodeTree{1};
    root->left->right = new NodeTree{3};
    root->right->left = new NodeTree{4};
    root->right->right = new NodeTree{8};

    std::cout << is_valid_bin_tree(root) << std::endl;
}
