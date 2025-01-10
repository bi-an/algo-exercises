/*
 * @lc app=leetcode.cn id=2982 lang=cpp
 *
 * [2982] 找出出现至少三次的最长特殊子字符串 II
 */

// @lc code=start
// 和 「2981. 找出出现至少三次的最长特殊子字符串 I」是相同的题目，只是数值范围变大了
// 放弃排序，建堆取前 3 大即可
// 时间复杂度：O(n)
class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();
        vector<int> groups[26];
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            ++cnt;
            // 根据下一个字符，来决定是否处理当前字符
            if (i + 1 == n || s[i] != s[i + 1]) {
                groups[s[i] - 'a'].push_back(cnt);
                cnt = 0;
            }
        }

        int ans = 0;
        for (auto& g : groups) {
            if (g.empty())
                continue;
            // 没必要排序，建最大堆，取前 3 大即可
            make_heap(g.begin(), g.end());  // 默认是用 less<> 比较器，是最大堆
            // 插入两个 0 ，防止访问越界
            g.push_back(0);
            g.push_back(0);

            int m = g.size();
            for (int i = 0; i < 3; ++i)
                pop_heap(g.begin(), g.end() - i);

            ans = max({ans, max(0, g[m - 1] - 2), min(g[m - 1] - 1, g[m - 2]), g[m - 3]});
        }

        return ans ? ans : -1;
    }
};
// @lc code=end
