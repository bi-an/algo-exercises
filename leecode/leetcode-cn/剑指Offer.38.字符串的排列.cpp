/*
 * @Author: your name
 * @Date: 2020-11-02 22:35:53
 * @LastEditTime: 2021-08-22 23:45:54
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\剑指Offer.38.字符串的排列.cc
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// 与`leetcode 47.全排列II' 相同
// 剑指offer提供的测试集不完善，提供的解法在leetcode上通不过，例如"fxx"。

class Solution {
public:
	vector<string> permutation(string s) {
		vector<string> res;
		sort(s.begin(), s.end());

		string path;
		path.reserve(s.size());
		vector<bool> visited(s.size());
		backtrace(res, s, path, visited, 0);

		return res;
	}

	void backtrace(vector<string>& res, string& s, string& path, vector<bool>& visited, int depth) {
		if (depth == s.size()) {
			res.push_back(path);
			return;
		}
		for (int i = 0; i < s.size(); i++) {
			if (visited[i] || i > 0 && s[i] == s[i - 1] && !visited[i-1])
				continue;
			path.push_back(s[i]);
			visited[i] = true;
			backtrace(res, s, path, visited, depth + 1);
			path.pop_back();
			visited[i] = false;
		}
	}
};