#include <iostream>
#include <stack>
#include <vector>
using namespace std;

/**
 * @brief 回溯法（DFS）
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
			path.pop_back();
			used[i] = false;
		}
	}
};