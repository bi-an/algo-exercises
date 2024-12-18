/*
 * @lc app=leetcode.cn id=2875 lang=cpp
 *
 * [2875] 无限数组的最短子数组
 */

// @lc code=start
class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int ans = target + 1, n = nums.size();
        long long sum = 0, tot = 0;
        for (auto x : nums) {
            tot += x;
            if (tot > target) break;
        }
        int k = target % tot;
        // 左闭右开区间
        for (int l = 0, r = 0; l < n; ++l) {
            // 注意到 target 可达 10⁹ ，这里可能超时
            while (sum < k) sum += nums[(r++) % n];
            if (sum == k) ans = min(ans, r - l);
            sum -= nums[l];
        }
        // ans += target / tot * n;
        return ans < target + 1 ? (long long)ans + target / tot * n : -1;
    }
};
// @lc code=end

// 写法二
namespace solution_2 {

class Solution {
public:
    int minSizeSubarray(vector<int>& nums, int target) {
        int ans = target + 1, n = nums.size();
        // reduce函数需要使用long long初始化，防止溢出
        long long sum = 0, tot = reduce(nums.begin(), nums.end(), 0LL);
        int k = target % tot;
        // 左闭右开区间
        for (int l = 0, r = 0; l < n; ++l) {
            // 注意到 target 可达 10⁹ ，如果直接将 sum 和 target 比较，可能超时
            while (sum < k)
                sum += nums[r++ % n];
            if (sum == k)
                ans = min(ans, r - l);
            sum -= nums[l];
        }
        ans += target / tot * n;
        return ans < target + 1 ? ans : -1;
    }
};

}  // namespace solution_2
