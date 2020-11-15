#include <bits/stdc++.h>
using namespace std;

/**
 * @file 1118.一个月有多少天.cc
 * @brief 给你一个数组T，这个数组存放的是近几天的天气气温，你返回一个等长的数组，
 * 计算：对于每一天，你还要至少等多少天才能等到一个更暖和的气温；如果等不到那一天，填 0。
 * 
 * 函数签名如下：
 * 
 * vector<int> dailyTemperatures(vector<int>& T);
 * 比如说给你输入T = [73,74,75,71,69,76]，你返回[1,1,3,2,1,0]。
 * 
 * 解释：第一天 73 华氏度，第二天 74 华氏度，比 73 大，所以对于第一天，只要等一天就能等到一个更暖和的气温，后面的同理。
 * 
 * @ref labuladong
 * 这是【496.下一个更大元素】的简单变形
 */

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& T) {
		vector<int> res(T.size());
		if (T.empty()) return res;

		// S存储的是下标
		stack<int> S;
		for (int i = T.size() - 1; i >= 0; i--) {
			while (!S.empty() && T[S.top()] <= T[i])
				S.pop();
			res[i] = S.empty() ? 0 : (S.top() - i);
			S.push(i);
		}

		return res;
	}
};