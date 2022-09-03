class Solution {
    vector<string> ans;
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root, "");
        return ans;
    }

    void dfs(TreeNode* root, string path) {
        if (root) {
            path += to_string(root->val);
            if (!root->left && !root->right) { // 叶子节点
                ans.push_back(path);
            } else {
                path += "->";
                dfs(root->left, path);
                dfs(root->right, path);
            }
        }
    }
};