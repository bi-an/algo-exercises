/*
 * @lc app=leetcode.cn id=1456 lang=cpp
 *
 * [1456] 定长子串中元音的最大数目
 */

// @lc code=start
// 定长滑动窗口
class Solution {
public:
    int maxVowels(string s, int k) {
        int cnt = 0, max_cnt = 0;
        for (int i = 0; i < s.length(); ++i) {
            int l = i - k >= 0 ? isVowel(s[i - k]) : 0;
            int r = isVowel(s[i]);
            cnt = cnt + r - l;
            max_cnt = max(max_cnt, cnt);
        }
        return max_cnt;
    }

    bool isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
};
// @lc code=end
