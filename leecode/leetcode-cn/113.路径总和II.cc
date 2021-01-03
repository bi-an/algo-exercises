/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> res;
		vector<int> path;
		if (root == nullptr) return res;
		dfs(res, path, 0, root, sum);
		return res;
	}

	void dfs(vector<vector<int>> &res, vector<int> path, int len, TreeNode* root, int sum) {
		if(root == nullptr) return;
        len += root->val;
        path.push_back(root->val);
        if(root->left == nullptr && root->right == nullptr && len == sum) {
            res.push_back(path);
            return;
        }
        dfs(res, path, len, root->left, sum);
        dfs(res, path, len, root->right, sum);
	}
};