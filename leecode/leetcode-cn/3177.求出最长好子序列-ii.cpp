/*
 * @lc app=leetcode.cn id=3177 lang=cpp
 *
 * [3177] 求出最长好子序列 II
 */

// @lc code=start

// 动态规划
// dp[v][j] 表示的是以数字 v 结尾，并且最多允许 j 个不同元素（即k=j）的最长子序列长度
// zd[j] 表示k=j，且本次迭代到v=nums[i]时，能获得的最长子序列长度

// 我们观察到我们进行状态转移时，是对数字的值进行比较，并没有利用到其下标，
// 所以将dp[i][j]改为dp[v][j]，以节约空间。

// 来自 @(lai)[https://leetcode.cn/u/lai-a9/] 的题解注释
// 
// 输入：nums = [1,2,1,1,3], k = 2
// 
// dp = []
// zd = [0, 0, 0]
// dp = [
//   [1, 1, 1], // 对于数字1
// ]
// zd = [1, 1, 1]
// dp = [
//   [1, 2, 2], // 对于数字2
//   [1, 1, 1], // 对于数字1
// ]
// zd = [1, 2, 2]
// dp = [
//   [1, 2, 2], // 对于数字2
//   [2, 2, 3], // 对于数字1
// ]
// zd = [2, 2, 3]
// dp = [
//   [1, 2, 2], // 对于数字2
//   [3, 3, 4], // 对于数字1
// ]
// zd = [3, 3, 4]
// dp = [
//   [1, 4, 4], // 对于数字3
//   [1, 2, 2], // 对于数字2
//   [3, 3, 4], // 对于数字1
// ]
// zd = [3, 4, 4]

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int len = nums.size();
        unordered_map<int, vector<int>> dp;
        vector<int> zd(k + 1, 0);

        for (int i = 0; i < len; i++) {
            int v = nums[i]; // 我们又遇到了数字v
            if (!dp.count(v)) {
                dp[v] = vector<int>(k + 1, 0);
            }

            auto& tmp = dp[v];
            for (int j = 0; j <= k; j++) {
                ++tmp[j]; // dp[v][j]表示以v结尾、最多不超过j个“与后项不等”的项的序列最长长度
                          // 我们又遇到了数字v，所以可以将数字v放在序列末尾，新序列也同样满足以上定义，
                          // 序列长度加1.
                          // 这是最基础的操作，即使j=0（即k=0）也必须更新，因为此时序列长度也可以延伸。
                          // k=0表示最多只有0个项与后项相等，也就是所有项都相等。
                if (j > 0) { // j=0时使用初始值就可以了，不需要状态转移
                    tmp[j] = max(tmp[j], zd[j - 1] + 1); // 这一步结合上一步++tmp[j]，也就是状态转移方程
                                                         // dp[v][j] = max(dp[v][j]+1, zd[j-1]+1)
                                                         // 也就是把v放在{...,v} (k=j)末尾，或
                                                         // 放在{...,x} (k=j-1,x与v可等可不等)末尾，取最大长度
                }
            }
            // 更新zd，也就是更新为dp[v][j]每一列的最大值，见上面的举例
            for (int j = 0; j <= k; j++) {
                zd[j] = max(zd[j], tmp[j]);
            }
        }
        return zd[k];
    }
};

namespace solution_2 {
// 代码和上面一模一样，上面废话有点多，这里简化了。
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        // dp[v][j] 表示k=j、以v结尾的序列的最长长度
        unordered_map<int, vector<int>> dp;
        // zd[j] 表示k=j，本次迭代（迭代nums[i]）能达到的最长序列长度
        vector<int> zd(k + 1);

        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            if (!dp.count(v)) {
                dp[v] = vector<int>(n + 1, 0);
            }
            auto& tmp = dp[v];
            for (int j = 0; j <= k; ++j) {
                ++tmp[j]; // 将当前v放入{...,v}之后，j=0时也可以扩展
                if (j > 0) { // j>0时还需进行状态转移
                    // zd[j-1]+1 表示将v放在k=j-1时序列{...,x}后面，
                    // 其中v=x或v≠x都可以，因为新序列的k不可能超过j
                    tmp[j] = std::max(tmp[j], zd[j - 1] + 1);
                }
            }
            for (int j = 0; j <= k; ++j) {
                zd[j] = std::max(zd[j], tmp[j]);
            }
        }
        return zd[k];
    }
};
} // namespace solution_2
// @lc code=end

