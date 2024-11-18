class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return getHeight(root) != -1;
    }

    // @return -1 标志不高度平衡。
    int getHeight(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1)
            return -1;
        return max(leftHeight, rightHeight) + 1;
    }
};