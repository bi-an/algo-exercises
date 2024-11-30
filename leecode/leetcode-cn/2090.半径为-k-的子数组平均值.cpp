/*
 * @lc app=leetcode.cn id=2090 lang=cpp
 *
 * [2090] 半径为 k 的子数组平均值
 */

// @lc code=start
class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size(), len = 2 * k + 1;
        vector<int> avgs(n, -1);
        long long sum = 0;
        // i 是右端点
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            // 左端点
            if (i - len + 1 < 0)
                continue;  // 也可以直接用 std::accumulate 算出最左边的窗口的平均值
                           // 然后 i 从合法值开始遍历
            avgs[i - k] = sum / len;
            // 删除左端点，为下一次作准备
            sum -= nums[i - len + 1];
        }
        return avgs;
    }
};
// @lc code=end
