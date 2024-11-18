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

// @ref labuladong
// 后续遍历
class Solution {
public:
    int maxSumBST(TreeNode* root) {
        maxSum = 0; // 注意：不能初始化为INT_MIN，因为null也是BST，如果节点全部为负值，那么直接返回空树就可以了
        traverse(root);
        return maxSum;
    }

    // res记录4个值：是否是BST，以root为根的当前BST的最小值，以root为根的当前BST的最大值，当前子树的键值和
    // 后续遍历：恰好能够求出这些值。假设已知左右子树的这些值，然后只需与root比较，就可以推断出当前树的这些值
    vector<int> traverse(TreeNode* root) {
        if(root == nullptr) 
            return vector<int>{1, INT_MAX, INT_MIN, 0}; // 这个初始化很巧妙

        vector<int> res(4);

        // 后续遍历
        vector<int> left = traverse(root->left);
        vector<int> right = traverse(root->right);

        // 左右子树都是BST，并且root->val也满足BST
        if(left[0] == 1 && right[0] == 1 && root->val > left[2] && root->val < right[1]) { // 是BST
            res[0] = 1;
            res[1] = min(left[1], root->val); // 为了与初始值比较
            res[2] = max(right[2], root->val); // 为了与初始值比较
            res[3] = left[3] + right[3] + root->val;
            maxSum = max(res[3], maxSum);
        } else {
            res[0] = 0; // 其他值没必要记录了
        }

        return res;
    }

private:
    int maxSum;
};