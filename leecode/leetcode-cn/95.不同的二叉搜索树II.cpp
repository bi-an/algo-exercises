// 回溯法
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        return recur(1, n);
    }

    vector<TreeNode*> recur(int start, int end) {
        if (start > end)
            return { nullptr }; // 注意：返回值一定不能为空，即使是 nullptr.
        vector<TreeNode*> roots;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> lefts = recur(start, i - 1);
            vector<TreeNode*> rights = recur(i + 1, end);
            for (TreeNode* left : lefts) {
                for (TreeNode* right : rights) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    roots.push_back(root);
                }
            }
        }
        return roots;
    }
};