/*
 * @lc app=leetcode.cn id=3162 lang=cpp
 *
 * [3162] 优质数对的总数 I
 */

// @lc code=start
// 和「3164.优质数对的总数-ii」是相同的题目
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<long long,int> cnt2;
        for (int x : nums2) {
            cnt2[static_cast<long long>(x) * k]++;
        }
        long long ans = 0;
        for (int num1 : nums1) {
            // 求 num1 的所有因子
            for (int x = 1; x * x <= num1; ++x) {
                if (num1 % x)
                    continue;
                if (cnt2.contains(x))
                    ans += cnt2[x];
                int y = num1 / x;
                if (y != x && cnt2.contains(y))
                    ans += cnt2[y];
            }
        }
        return ans;
    }
};
// @lc code=end

