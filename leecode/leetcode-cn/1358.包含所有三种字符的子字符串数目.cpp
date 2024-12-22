/*
 * @lc app=leetcode.cn id=1358 lang=cpp
 *
 * [1358] 包含所有三种字符的子字符串数目
 */

// @lc code=start
// 不定长滑动窗口
// “越长越合法”：一般要写 ans += left
class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.length(), ans = 0, m = 3;
        vector<int> cnt(3);
        for (int l = 0, r = 0; r < n; ++r) {
            if (cnt[s[r] - 'a']++ == 0)
                --m;
            // 先找最小的区间
            while (l <= r && cnt[s[l] - 'a'] > 1)
                --cnt[s[l++] - 'a'];
            if (m == 0)
                ans += l + 1;  // ans+=left+1 因为最小区间加上左边任意长度都是合法的
        }
        return ans;
    }
};
// @lc code=end
