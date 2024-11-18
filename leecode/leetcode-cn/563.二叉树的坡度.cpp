/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    int tilt = 0;

public:
    int findTilt(TreeNode* root) {
        dfs(root);
        return tilt;
    }

    int dfs(TreeNode* root) {
        if(!root)
            return 0;
        int sumLeft = dfs(root->left);
        int sumRight = dfs(root->right);
        tilt += abs(sumLeft - sumRight);
        return sumLeft + sumRight + root->val;
    }
};