/*
 * @lc app=leetcode.cn id=2537 lang=cpp
 *
 * [2537] 统计好子数组的数目
 */

// @lc code=start
class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long ans = 0;
        unordered_map<int, int> cnt;
        int pairs = 0, n = nums.size();
        for (int l = 0, r = 0; r < n; ++r) {
            // 每增加一个频次，新增的对数等于原来的频次（新数与原来每个数都能成一对）。
            pairs += cnt[nums[r]]++;
            // 同理，每减少一个频次，减少的对数等于减少后的频次（与剩余的每个数都组成过一个对，现在这些对消失了）。
            while (pairs >= k)
                pairs -= --cnt[nums[l++]];
            ans += l;
        }
        return ans;
    }
};
// @lc code=end
