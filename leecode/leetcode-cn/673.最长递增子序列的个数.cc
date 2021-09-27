/*
 * @Author: your name
 * @Date: 2021-09-27 23:33:21
 * @LastEditTime: 2021-09-27 23:35:02
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\673.最长递增子序列的个数.cc
 */

// 动态规划
// 时间复杂度
class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {
		int n = nums.size(), maxLen = 0, ans = 0;
        // dp[i] 以nums[i]结尾的最长递增子序列的长度
        // cnt[i] 以nums[i]结尾的最长递增子序列的个数
		vector<int> dp(n), cnt(n);
		for (int i = 0; i < n; i++) {
			dp[i] = 1;
			cnt[i] = 1;
			for (int j = 0; j < i; j++) {
				if (nums[i] > nums[j]) {
					if (dp[j] + 1 > dp[i]) {
						dp[i] = dp[j] + 1;
						cnt[i] = cnt[j]; // 容易错
					}
					else if (dp[j] + 1 == dp[i]) {
						cnt[i] += cnt[j];
					}
				}
			}
			if (maxLen < dp[i]) {
				maxLen = dp[i];
				ans = cnt[i];
			}
			else if (maxLen == dp[i]) {
				ans += cnt[i];
			}
		}
		return ans;
	}
};