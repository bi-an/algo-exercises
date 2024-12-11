/*
 * @lc app=leetcode.cn id=2968 lang=cpp
 *
 * [2968] 执行操作使频率分数最大
 */

// @lc code=start
// 题解：https://leetcode.cn/problems/apply-operations-to-maximize-frequency-score/solutions/2569301/hua-dong-chuang-kou-zhong-wei-shu-tan-xi-nuvr/
// 定理：将数组 a 的所有元素变为 a 的中位数是最优的。证明见题解。
class Solution {
public:
    int maxFrequencyScore(vector<int>& nums, long long k) {
        sort(nums.begin(), nums.end());
        int n = nums.size(), ans = 0;
        vector<long long> preSum(n + 1);
        for (int i = 0; i < n; ++i) {
            preSum[i + 1] = preSum[i] + nums[i];
        }
        for (int left = 0, right = 0; right < n; ++right) {
            // 计算代价的逻辑可以提取成函数
            int mid = (left + right) / 2;
            // (1) 如果是奇数个元素，那么，
            // 左边代价：中位数 - 每个元素
            // 右边代价：每个元素 - 中位数
            // 左右求和则中位数项相消。
            // (2) 如果是偶数个元素，那么左边元素比右边少一个，所以结果中需要再减去一个中位数。
            while ((preSum[right + 1] - preSum[mid + 1]) - (preSum[mid] - preSum[left]) - ((right - left + 1) & 1 ? 0 : nums[mid]) > k) {
                mid = (++left + right) / 2;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
// @lc code=end
