// 参考：[一篇文章解决所有二叉树路径问题](https://leetcode.cn/problems/longest-univalue-path/solution/yi-pian-wen-zhang-jie-jue-suo-you-er-cha-94j7/)
class Solution {
    int maxLen;
public:
    int longestUnivaluePath(TreeNode* root) {
        maxLen = 0;
        dfs(root);
        return maxLen;
    }

    // 包含 root 的最长同值路径
    int dfs(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        if (root->left && root->val == root->left->val)
            left = left + 1;
        else
            left = 0; // 一定要包含 root，因为下一次需要和当前树的父节点形成路径。
        if (root->right && root->val == root->right->val)
            right = right + 1;
        else
            right = 0;
        maxLen = max(maxLen, left + right);
        return max(left, right); // 只能返回最大同值深度，因为下一次需要和当前树的父节点形成路径。
    }
};