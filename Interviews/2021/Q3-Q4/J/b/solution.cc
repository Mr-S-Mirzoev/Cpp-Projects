#include <iostream>
#include <stack>

template <typename T>
class TreeNode
{
    T value_;
    TreeNode* left_ = nullptr;
    TreeNode* right_ = nullptr;

public:
    TreeNode(T const& value) : value_(value) {}

    /*
    Tree example:
        1
      2   3
     * 5 6 7

    IDEA (Morris traversal):

    def inorderTraversal(self, root):
        result=[]
        node=root
        while node!=None:
            if node.left==None:
                result.append(node.val)
                node=node.right
            else:
                pre=node.left
                while pre.right!=None and pre.right!=node:
                    pre=pre.right
                if pre.right==None:
                    pre.right=node
                    node=node.left
                else:
                    pre.right=None
                    result.append(node.val)
                    node=node.right
        return result
    */
    static void traverse(TreeNode* root)
    {
        TreeNode* node = root;
        TreeNode* prev;

        while (node)
        {
            if (node->left_ == nullptr)
            {
                std::cout << node->value_ << std::endl;
                node = node->right_;
            }
            else
            {
                prev = node->left_;
                while (prev->right_ && prev->right_ != node)
                    prev = prev->right_;

                if (prev->right_ == nullptr)
                {
                    prev->right_ = node;
                    node = node->left_;
                }
                else
                {
                    prev->right_ = nullptr;
                    std::cout << node->value_ << std::endl;
                    node = node->right_;
                }
            }
        }
    }
    static TreeNode* from_type(unsigned val, char type)
    {
        if (type == '*')
            return new TreeNode(val);

        return nullptr;
    }
    static TreeNode* build_tree(std::string const& s);
};

class TreeException : public std::logic_error
{
public:
    TreeException(const std::string& s) : std::logic_error("TreeExc: " + s) {}
};

template <typename T>
TreeNode<T>* TreeNode<T>::build_tree(std::string const& s)
{
    std::stack<TreeNode*> parents;
    TreeNode* root;

    auto len = s.length();
    std::size_t i = 2;
    unsigned long id = 1;
    if (len < 2)
        throw TreeException("Invalid tree string: " + s);

    root = TreeNode::from_type(id, s[1]);
    bool left = true;

    TreeNode* current = root;
    TreeNode* added;
    while (i < len)
    {
        if (s[i] == ',')
        {
            left = !left;
            ++i;
        }
        else if (s[i] == '(')
        {
            left = !left;
            parents.push(current);
            id <<= 1;

            if (left)
            {
                added = TreeNode::from_type(id, s[i + 1]);
                parents.top()->left_ = added;
            }
            else
            {
                id += 1;
                added = TreeNode::from_type(id, s[i + 1]);
                parents.top()->right_ = added;
            }

            i += 2;
            current = added;
        }
        else if (s[i] == ')')
        {
            left = !left;
            id >>= 1;
            if (i != len - 1)
            {
                current = parents.top();
                parents.pop();
            }

            ++i;
        }
    }

    return root;
}

typedef TreeNode<unsigned> TreeNodeU;

int main(int argc, char const* argv[])
{
    /*
    Bracket representation of:
          1
        2   3
       * 5 6 7

    * = has value
    - = has no value
    */
    TreeNodeU* root = TreeNodeU::build_tree("(*,(*,(-),(*)),(*,(*),(*)))");
    TreeNodeU::traverse(root);
    return 0;
}
