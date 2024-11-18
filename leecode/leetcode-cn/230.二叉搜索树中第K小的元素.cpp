// 中序遍历：递归
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        return dfs(root, k);
    }

    int dfs(TreeNode* root, int& k) {
        if (root == nullptr)
            return -1;

        int leftVal = dfs(root->left, k);
        if (leftVal != -1)
            return leftVal;
        if (--k == 0)
            return root->val;
        return dfs(root->right, k);
    }
};