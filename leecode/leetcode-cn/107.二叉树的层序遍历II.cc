// BFS
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> Q;
        if (root != nullptr)
            Q.push(root);
        while (!Q.empty()) {
            int width = Q.size();
            vector<int> level(width);
            for (int i = 0; i < width; ++i) {
                TreeNode* cur = Q.front();
                Q.pop();
                level[i] = cur->val;
                if (cur->left)
                    Q.push(cur->left);
                if (cur->right)
                    Q.push(cur->right);
            }
            ans.push_back(level);
        }
        reverse(ans.begin(), ans.end()); // 多一个翻转的步骤
        return ans;
    }
};