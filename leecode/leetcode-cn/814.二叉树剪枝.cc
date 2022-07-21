// 递归
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if (root == nullptr)
            return root;
        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if (root->val == 0 && !root->left && !root->right) {
            delete root;
            // cout << "delete " << root << endl;
            return nullptr;
        }
        return root;
    }
};