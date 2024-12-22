/*
 * @lc app=leetcode.cn id=2962 lang=cpp
 *
 * [2962] 统计最大元素出现至少 K 次的子数组
 */

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        int n = nums.size(), x = ranges::max(nums), cnt = 0;
        for (int l = 0, r = 0; r < n; ++r) {
            cnt += nums[r] == x;
            // 先找最小区间
            while (l <= r && (cnt > k || nums[l] != x))
                cnt -= nums[l++] == x;
            if (cnt >= k)
                ans += l + 1;  // 最小区间加上左边任意长度都合法
        }
        return ans;
    }
};

namespace version_2 {
// @lc code=start
// 写法二
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        int n = nums.size(), x = ranges::max(nums), cnt = 0;
        for (int l = 0, r = 0; r < n; ++r) {
            cnt += nums[r] == x;
            // 先找最小区间
            while (l <= r && cnt >= k)
                cnt -= nums[l++] == x;
            // 由于只有区间合法时，left 才会右移，并且一直移动到最小区间的下一个位置
            // 所以只要 left > 0 ，就一定是合法的
            ans += l;  // 最小区间加上左边任意长度都合法
        }
        return ans;
    }
};
// @lc code=end
}  // namespace version_2
