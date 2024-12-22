/*
 * @lc app=leetcode.cn id=3298 lang=cpp
 *
 * [3298] 统计重新排列后包含另一个字符串的子字符串数目 II
 */

// @lc code=start
// 与「76. 最小覆盖子串」本质相同，即合法的 word1 子串中，每个字符的出现次数应该与 word2 中相同。
class Solution {
public:
    long long validSubstringCount(string word1, string word2) {
        long long ans = 0;
        // 定义 cnt[c]=cnt2[c]-cnt1[c]
        unordered_map<char, int> cnt;
        for (auto c : word2)
            ++cnt[c];
        // m 记录窗口中有多少数已经和 word2 抵消（出现次数也要抵消）
        int n = word1.length(), m = cnt.size();
        for (int l = 0, r = 0; r < n; ++r) {
            m -= --cnt[word1[r]] == 0;
            // 先找最小区间
            while (m == 0)
                m += cnt[word1[l++]]++ == 0;
            // left 指向最小区间左端点的下一个位置
            ans += l;  // 最小区间加上左边任意长度都合法
        }
        return ans;
    }
};
// @lc code=end
