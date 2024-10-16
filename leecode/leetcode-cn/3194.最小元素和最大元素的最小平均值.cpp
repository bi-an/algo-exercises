/*
 * @lc app=leetcode.cn id=3194 lang=cpp
 *
 * [3194] 最小元素和最大元素的最小平均值
 */

// @lc code=start
class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        // double res = numeric_limits<double>::max();
        int ans = INT_MAX, n = nums.size();
        for (int i = 0; i < n/2; ++i) {
            // 除以 2 之后，小数位要么为 0.0 ，要么为 0.5
            // 其实没有必要考虑浮点数误差
            ans = min(ans, (nums[i] + nums[n-1-i]) * 10 / 2);
        }
        return (double)ans / 10;
    }
};
// @lc code=end

