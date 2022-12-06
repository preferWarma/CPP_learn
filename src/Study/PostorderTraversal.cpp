/*统一迭代法后序遍历*/
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<int> postorderTraversal(TreeNode *root)
{
    if (!root)
        return {};
    vector<int> result;
    stack<TreeNode *> stk;
    stk.push(root);
    while (!stk.empty())
    {
        TreeNode *node = stk.top();
        stk.pop();
        if (node)
        {
            stk.push(node);
            stk.push(nullptr);
            if (node->right)
            {
                stk.push(node->right);
            }
            if (node->left)
            {
                stk.push(node->left);
            }
        }
        else
        {
            result.push_back(stk.top()->val);
            stk.pop();
        }
    }
    return result;
}

int main()
{

    return 0;
}