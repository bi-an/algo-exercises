/*
 * @Author: your name
 * @Date: 2021-08-23 23:35:23
 * @LastEditTime: 2021-08-24 00:05:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\526.优美的排列.cc
 */

// 标准回溯法
// 效率较低
class Solution {
public:
	int countArrangement(int n) {
		vector<int> path(1);
		vector<bool> visited(n + 1, false);
		int ans = 0;
		backtrace(ans, path, visited, 0, n);
		return ans;
	}

	void backtrace(int& ans, vector<int>& path, vector<bool>& visited, int depth, int n) {
		if (depth == n) {
			ans++;
			return;
		}
		for (int i = 1; i <= n; i++) {
			if (visited[i])
				continue;
			visited[i] = true;
			path.push_back(i);
			int j = path.size() - 1;
			if (i % j == 0 || j % i == 0)
				backtrace(ans, path, visited, depth + 1, n);
			visited[i] = false;
			path.pop_back();
		}
	}
};

// 优化后的回溯法
class Solution {
public:
    int countArrangement(int n) {
        int ans = 0;
        vector<vector<int>> match(n+1);
        vector<bool> visited(n+1, false);
        // 预处理优化
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                if(i%j == 0 || j % i == 0) {
                    // 在某种排列的第i个位置，可能符合条件的元素为j；这里“可能”表示该种排列中可能有重复元素，这种不符合要求；
                    // 是否有重复元素，可以用visited数组来标记
                    match[i].push_back(j);
                }
            }
        }
        backtrace(ans, match, visited, 1, n);
        return ans;
    }

    void backtrace(int& ans, vector<vector<int>>& match, vector<bool>& visited, int index, int n) {
        if(index == n + 1) {
            ans++;
            return;
        }
        for(auto x : match[index]) {
            if(!visited[x]) {
                visited[x] = true;
                backtrace(ans, match, visited, index+1, n);
                visited[x] = false;
            }
        }
    }   
};