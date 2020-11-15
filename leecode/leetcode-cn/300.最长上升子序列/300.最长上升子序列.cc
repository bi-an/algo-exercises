#include <bits/stdc++.h>
using namespace std;

/**
 * @ref labuladong
 * 
 */

// 动态规划
// 时间复杂度O(n^2)，空间复杂度O(n)
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;

		int n = nums.size();
		// dp[i]表示以第i个字符结尾（一定包含该字符）的子序列中，最长的长度
        // 注意：dp[i]不是最优值
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


// 模拟纸牌Patience Solitaire
// 纸牌的堆数就是最长子序列长度，证明见《LongestIncreasingSubsequence.pdf》
// 时间复杂度O(nlogn)，空间复杂度O(n)
class Solution_2 {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;

		int piles = 0;
        // top是有序的，所以可以使用二分法
        vector<int> top(nums.size());
        for(int i=0;i<nums.size();i++){
            int left = 0, right = piles - 1;
			// 左边界的二分查找法
            while(left <= right){
                int mid = (left+right)/2;
                if(top[mid] >= nums[i]){
                    right = mid - 1; // 即使等于，也要不断往左寻找
                }
                else {
                    left = mid+1;
                }
            }
            // 没有合适的堆，则新建一个
            if(left == piles){
                top[piles++] = nums[i];
            }
            else{
                top[left] = nums[i];
            }
        }

        return piles;
	}
};