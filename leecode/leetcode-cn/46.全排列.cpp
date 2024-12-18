#include <iostream>
// #include <stack>
#include <vector>
#include <queue>
using namespace std;

/**
 * @brief 回溯法（DFS）
 * 
 * 回溯法本质上是遍历
 * 
 * 先画出递归树，然后DFS或者BFS
 * 
 * 三个状态变量
 * 1. path: stack
 * 2. used
 * 3. depth
 */

class Solution
{
public:
	vector<vector<int>> permute(vector<int> &nums)
	{
		vector<vector<int>> res;
		if (nums.empty())
			return res;

		vector<int> path; // 栈
        path.reserve(nums.size());
		vector<bool> used(nums.size());

		dfs(res, nums, path, used, 0);
		return res;
	}

    // 除了res，其他参数的引用类型可以改为值类型，引用类型可以降低内存和提高运行速度
	void dfs(vector<vector<int>> &res, vector<int> &nums, vector<int>& path, vector<bool>& used, int depth)
	{
		if (depth == nums.size())
		{
			res.push_back(path);
			return;
		}
		for (int i = 0; i < nums.size(); i++)
		{
			if (used[i])
				continue;
			path.push_back(nums[i]);
			used[i] = true;
			dfs(res, nums, path, used, depth + 1);
			// 状态回退
			path.pop_back();
			used[i] = false;
		}
	}
};