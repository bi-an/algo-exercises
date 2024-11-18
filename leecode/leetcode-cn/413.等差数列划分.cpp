/**
 * 参考题解： https://leetcode-cn.com/problems/arithmetic-slices/solution/hua-dong-chuang-kou-dong-tai-gui-hua-jav-3vpp/
 */ 

// 方法一：双指针


// 方法二：动态规划
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        vector<int> dp(n, 0); // dp[i]表示以nums[i]结尾、长度大于等于3的连续等差数列的个数

        for(int i=2;i<n;i++) {
            if(nums[i] - nums[i-1] == nums[i-1] - nums[i-2]) {
                dp[i] = dp[i-1] + 1; // 之前的等差数列加上nums[i]，显然都构成新的等差数列；并且，倒数3个数构成一个之前没有计入的等差数列
                ans += dp[i];
            }
        }

        return ans;
    }
};