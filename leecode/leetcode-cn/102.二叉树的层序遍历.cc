class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr)
            return {};
        vector<vector<int>> ans;
        queue<TreeNode*> Q;
        Q.push(root);
        while (!Q.empty()) {
            int width = Q.size();
            vector<int> level;
            for (int i = 0; i < width; ++i) {
                TreeNode* cur = Q.front();
                if (cur->left)
                    Q.push(cur->left);
                if (cur->right)
                    Q.push(cur->right);
                level.push_back(cur->val);
                Q.pop();
            }
            ans.push_back(level);
        }
        return ans;
    }
};