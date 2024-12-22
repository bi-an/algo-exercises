/*
 * @lc app=leetcode.cn id=3258 lang=cpp
 *
 * [3258] 统计满足 K 约束的子字符串数量 I
 */

// @lc code=start
class Solution {
public:
    int countKConstraintSubstrings(string s, int k) {
        int ans = 0, n = s.length(), cnt[2]{};
        for (int l = 0, r = 0; r < n; ++r) {
            ++cnt[s[r] - '0'];
            while (cnt[0] > k && cnt[1] > k)
                --cnt[s[l++] - '0'];
            // 窗口内所有子串都合法
            // 为了避免重复计入，要求这些子串必须包含 s[right]
            ans += r - l + 1;
        }
        return ans;
    }
};
// @lc code=end
