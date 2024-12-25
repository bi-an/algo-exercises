/*
 * @lc app=leetcode.cn id=992 lang=cpp
 *
 * [992] K 个不同整数的子数组
 */

// @lc code=start
class Solution {
    // 不同整数个数 ≤ k 个的子数组个数
    int f(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        unordered_map<int, int> cnt;
        for (int l = 0, r = 0; r < n; ++r) {
            cnt[nums[r]]++;
            while (cnt.size() > k) {
                int x = nums[l++];
                if (--cnt[x] == 0)
                    cnt.erase(x);
            }
            ans += r - l + 1;
        }
        return ans;
    }

public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // cnt < k 等价于 cnt ≤ k - 1
        return f(nums, k) - f(nums, k - 1);
    }
};
// @lc code=end
