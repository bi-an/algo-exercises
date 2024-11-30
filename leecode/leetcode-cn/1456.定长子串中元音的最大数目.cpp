/*
 * @lc app=leetcode.cn id=1456 lang=cpp
 *
 * [1456] 定长子串中元音的最大数目
 */

// @lc code=start
// 定长滑动窗口
// 本题不是典型题解模板，典型题解请参照「643.子数组最大平均数 I」
class Solution {
public:
    int maxVowels(string s, int k) {
        // 本题特殊：计数总是大于等于0，所以初始值为 0 .
        int cnt = 0, max_cnt = 0;
        for (int i = 0; i < s.length(); ++i) {
            int l = i - k >= 0 ? isVowel(s[i - k]) : 0;
            int r = isVowel(s[i]);
            // 注意到本题的特殊之处：
            // 当窗口扩大时，cnt 总是非递减的；反之当窗口缩小时，总是非递增的
            // 所以可以每次都求 max ，而不需要管窗口长度是否为 k 。
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
