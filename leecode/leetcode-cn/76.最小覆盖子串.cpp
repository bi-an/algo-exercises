/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */

// @lc code=start
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length();
        // unordered_map<char, int> cnt_s, cnt_t;
        int cnt_s[128]{}, cnt_t[128]{};  // ASCII 共 128 个字符

        int m = 0;
        for (auto c : t) {
            if (cnt_t[c] == 0)
                ++m;
            ++cnt_t[c];
        }
        int ans_l = 0, ans_r = n;  // m = cnt_t.size();
        for (int l = 0, r = 0; r < n; ++r) {
            m -= ++cnt_s[s[r]] == cnt_t[s[r]];
            while (l <= r && cnt_s[s[l]] > cnt_t[s[l]])
                cnt_s[s[l++]]--;
            if (m == 0 && ans_r - ans_l > r - l) {
                ans_l = l;
                ans_r = r;
            }
        }
        return ans_r < n ? s.substr(ans_l, ans_r - ans_l + 1) : "";
    }
};
// @lc code=end
