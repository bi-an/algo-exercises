/*
 * @lc app=leetcode.cn id=1248 lang=cpp
 *
 * [1248] 统计「优美子数组」
 */

// @lc code=start
// 恰好型窗口
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int ans = 0, cnt1 = 0, cnt2 = 0;
        for (int l1 = 0, l2 = 0, r = 0; r < nums.size(); ++r) {
            int odd = nums[r] & 1;
            cnt1 += odd;
            cnt2 += odd;
            // cnt <= k 部分
            while (cnt1 > k)
                cnt1 -= nums[l1++] & 1;
            // cnt < k 部分
            // 有可能本来就等于 k （当 k = 0 时）
            while (l2 < nums.size() && cnt2 >= k)
                cnt2 -= nums[l2++] & 1;
            ans += l2 - l1;  // 差集
        }
        return ans;
    }
};
// @lc code=end
