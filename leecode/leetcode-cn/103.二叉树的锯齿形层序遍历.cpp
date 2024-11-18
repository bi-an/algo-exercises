// BFS
// 层序遍历 + 存储时下标正序、倒序交替。
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        queue<TreeNode*> Q;
        if (root)
            Q.push(root);
        bool fromLeft = true;
        while (!Q.empty()) {
            int width = Q.size();
            vector<int> level(width); // 可以使用双端队列。
            for (int i = 0; i < width; ++i) {
                TreeNode* cur = Q.front();
                if (cur->left)
                    Q.push(cur->left);
                if (cur->right)
                    Q.push(cur->right);
                Q.pop();
                if (fromLeft)
                    level[i] = cur->val;
                else
                    level[width - 1 - i] = cur->val;
            }
            ans.push_back(level);
            fromLeft = !fromLeft;
        }
        return ans;
    }
};

