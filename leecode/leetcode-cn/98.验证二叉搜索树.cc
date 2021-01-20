/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     long val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(long x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(long x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 后序遍历
// 这道题会用INT_MAX单节点树作为测试用例，所以要使用long类型
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        vector<long> res = traverse(root);
        return res[0];
    }

    // res包含3个值：是否为BST，以root为根的子树的最小值，以root为根的子树的最大值
    vector<long> traverse(TreeNode* root) {
        if(root == nullptr) 
            return vector<long>{1, LONG_MAX, LONG_MIN};
        
        vector<long> res(3);
        // 后序遍历
        vector<long> left = traverse(root->left);
        vector<long> right = traverse(root->right);

        if(left[0] == 1 && right[0] == 1 && root->val > left[2] && root->val < right[1]) {
            res[0] = 1; // 是BST
            res[1] = Min(left[1], root->val);
            res[2] = Max(right[2], root->val);
        } else {
            res[0] = 0; // 其他值没必要记录
        }

        return res;
    }

private:
    long Min(long a, long b) {
        return a < b ? a : b;
    }
    long Max(long a, long b) {
        return a > b ? a : b;
    }
};

// 前序遍历
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return traverse(root, nullptr, nullptr);
    }

    bool traverse(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(root == nullptr) return true;
        if(minNode && root->val <= minNode->val) return false;
        if(maxNode && root->val >= maxNode->val) return false;
        // 向左遍历，只有一个条件，就是最大值不得超过root，所以此时minNode一直为null
        // 向右遍历，同理
        // 换言之，minNode还是maxNode为nullptr，实际上标志了该节点是左子树还是右子树
        return traverse(root->left, minNode, root) && traverse(root->right, root, maxNode);
    }
};