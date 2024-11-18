// 方法一：DFS
// 时间复杂度：O(n^2)。
//     在最坏情况下，二叉树的上部分 n/2 个节点为链表；
//     下半部分 n/2 节点为完全二叉树（一棵 N 节点的完全二叉树的叶子节点的个数为 N/2）。
//     完全二叉树的叶子数参见：https://zhidao.baidu.com/question/527811815091104325.html
//     https://zhidao.baidu.com/question/527811815091104325.html
//     所以，此时路径数为 O(n)，每条路径长度为 O(n)。
//     所以要把这些路径都添加到答案中，总时间复杂度为 O(n^2)。
// 空间复杂度：O(n)。空间复杂度主要取决于栈空间的开销，栈中的元素个数不会超过树的节点数。
//
// 递归写法一
class Solution {
    vector<vector<int>> ans;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        dfs(root, targetSum, path);
        return ans;
    }

    void dfs(TreeNode* root, int targetSum, vector<int>& path) {
        if (root == nullptr)
            return;
        path.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == targetSum)
                ans.push_back(path);
        }
        dfs(root->left, targetSum - root->val, path);
        dfs(root->right, targetSum - root->val, path);
        path.pop_back(); // 注意恢复现场。
    }
};

// 方法一：DFS
// 递归写法二：递归函数使用值传递，效率较低。
class Solution {
    vector<vector<int>> ans;
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> path;
        dfs(root, targetSum, path);
        return ans;
    }

    void dfs(TreeNode* root, int targetSum, vector<int> path) {
        if (root == nullptr)
            return;
        path.push_back(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            if (root->val == targetSum)
                ans.push_back(path);
        }
        dfs(root->left, targetSum - root->val, path);
        dfs(root->right, targetSum - root->val, path);
    }
};

// 方法一：DFS
// 写法三
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

// 方法二：BFS
// TODO