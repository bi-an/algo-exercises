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
public:
    vector<TreeNode*> generateTrees(int n) {
        if(n<=0) return {};
        return helper(1, n);
    }

    vector<TreeNode*> helper(int lo, int hi){
        if(lo == hi) return {new TreeNode(lo)};
        if(lo > hi) return {nullptr};
        vector<TreeNode*> res;
        for(int i=lo;i<=hi;i++){
            for(TreeNode* left : helper(lo, i-1)){ // 左子树的节点都小于根
                for(TreeNode* right : helper(i+1, hi)){ // 右子树的节点都大于根
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    res.push_back(root);
                }
            }
        }
        return res;
    }
};