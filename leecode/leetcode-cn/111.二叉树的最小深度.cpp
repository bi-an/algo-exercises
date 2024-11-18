// 递归 DFS
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr)
            return 0;
        int leftDepth = minDepth(root->left);
        int rightDepth = minDepth(root->right);
        // 注意如下两种特殊情况：
        if (leftDepth == 0)
            return 1 + rightDepth;
        if (rightDepth == 0)
            return 1 + leftDepth;
        return 1 + min(leftDepth, rightDepth);
    }
};

// 方法二：BFS
// 层序遍历，当找到第一个叶子节点，就可以返回这个深度。
