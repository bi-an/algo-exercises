#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;

		int n = nums.size();
		// dp表示以第i个字符结尾（一定包含该字符）的子序列中，最长的长度
        // 注意：这里不是最优值
		vector<int> dp(n);
		for (int i = 0; i < n; i++)
			dp[i] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = i - 1; j >= 0; j--) {
                // 此时可以把nums[i]直接接到nums[j]后面，所以最长长度要加1
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}

		return *max_element(dp.begin(), dp.end());
	}
};