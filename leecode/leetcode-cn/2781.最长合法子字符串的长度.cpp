/*
 * @lc app=leetcode.cn id=2781 lang=cpp
 *
 * [2781] 最长合法子字符串的长度
 */

// @lc code=start
// 哈希表 + 滑动窗口
// 题解：https://leetcode.cn/problems/length-of-the-longest-valid-substring/solutions/2345796/ha-xi-biao-shuang-zhi-zhen-pythonjavacgo-bcez/
class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        int n = word.length(), ans = 0;
        unordered_set<string> fb{forbidden.begin(), forbidden.end()};

        for (int left = 0, right = 0; right < n; ++right) {
            // （1）之前的窗口合法，加入 right 之后就不合法，那么一定是 right 导致的。
            // （2）如果短串在 forbidden 内，那么增长后必然也不合法，故从 right 开始向左搜寻第一个短串（最短串）。
            // （3）题目已知 forbidden[i].length ≤ 10 ，可以提前结束对 left 的搜索，直接将时间复杂度降低了一个维度
            for (int i = right; i >= left && right - i <= 10; --i) {
                if (fb.count(word.substr(i, right - i + 1))) {
                    left = i + 1;
                    break;
                }
            }
            ans = max(ans, right - left + 1);·
        }

        return ans;
    }
};
// @lc code=end
