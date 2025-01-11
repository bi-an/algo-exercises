/*
 * @lc app=leetcode.cn id=392 lang=cpp
 *
 * [392] 判断子序列
 */

// @lc code=start
// 双指针
// 每个字符第一次匹配之后，永远不需要反悔
// 时间复杂度：O(n+m) ，每次无论是匹配成功还是失败，都有至少一个指针发生右移，两指针能够位移的总距离为 n+m。
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if (s.empty())
            return true;
        int i = 0, n = s.length();
        for (char c : t) {
            if (s[i] == c && ++i == n)
                return true;
        }
        return false;
    }
};
// @lc code=end
