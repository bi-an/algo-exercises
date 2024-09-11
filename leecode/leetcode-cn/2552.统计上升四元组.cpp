/*
 * @lc app=leetcode.cn id=2552 lang=cpp
 *
 * [2552] 统计上升四元组
 */

// @lc code=start
class Solution {
public:
    long long countQuadruplets(vector<int>& nums) {
        long long ans = 0;
        int n = nums.size();
        // vector会将pre默认初始化为0（使用int的默认初始化函数int())
        vector<int> pre(n + 1); // 前缀：pre[x]表示比nums[j]小的数（记作x）的个数
        // 注意j从左往右、k从右往左遍历，这样恰好符合前缀和后缀的计算顺序
        // j从0开始，k从n-1开始，这意味着我们在循环中会初始化pre和suf
        for (int j = 0; j < n - 2; ++j) {
            int suf = 0; // 后缀：符合条件的l的数目
            for (int k = n - 1; k > j; --k) {
                // 这个if-else的逻辑是：
                // 本题规定得非常巧合，所有的数字都不等，
                // 所以找到的数要么是 nums[l]，要么是nums[k]
                if (nums[j] > nums[k]) {
                    // 找到了一个 k
                    ans += static_cast<long long>(pre[nums[k]]) * suf;
                } else {
                    // 符合条件的 l 的数目
                    // 也就是比nums[j]大的数的个数
                    ++suf; // 当k=n-1时，初始化suf
                }
            }
            // 将所有比nums[j]大的数（即x）的个数都加1
            // 因为我们找到了一个比x小的数nums[j]
            // 能这么做的原因又是因为题设的巧合：我们知道x的范围为1~n
            // 注意到j从0开始，恰好符合我们找“nums[0]~nums[j]中比nums[k]小的数的个数”的顺序
            // 当j=0时，我们初始化pre
            for (int x = nums[j] + 1; x <= n; ++x) {
                ++pre[x];
            }
        }
        return ans;
    }
};
// @lc code=end

