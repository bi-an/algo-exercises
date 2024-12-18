/*
 * @lc app=leetcode.cn id=2904 lang=cpp
 *
 * [2904] 最短且字典序最小的美丽子字符串
 */

// @lc code=start
// 时间复杂度：O(n²) ，因为字符串比较字典序和子串切片需要 O(n) 。
// TODO: 注：利用字符串哈希（或者后缀数组等），可以把比较字典序的时间降至 O(nlogn)，这样可以做到 O(nlogn) 的时间复杂度。来源：https://leetcode.cn/problems/shortest-and-lexicographically-smallest-beautiful-string/solutions/2483144/mei-ju-pythonjavacgo-by-endlesscheng-5th8/
// 每次维护当前窗口内的字符串，然后通过滚动哈希来比较与 ans 的字典序；不进行字符串切片，而是保存一个 {start -> end} 的 pair 记录最优 ans。似乎可以做到整体 O(n) 。
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        // if (count(s.begin(), s.end(), '1') < k) {
        //     return "";
        // }
        // // 否则一定有解

        int n = s.length(), cnt = 0, len = -1;
        string ans(n + 1, ' ');
        for (int l = 0, r = 0; r < n; ++r) {
            cnt += s[r] == '1';
            while (l <= r && (s[l] == '0' || cnt > k))
                cnt -= s[l++] == '1';
            if (cnt == k) {
                string tmp = s.substr(l, r - l + 1);
                if (/*tmp.length()*/ r - l + 1 < ans.length() || tmp.length() == ans.length() && tmp < ans)
                    ans = tmp;
            }
        }
        return ans.length() <= n ? ans : "";
    }
};
// @lc code=end
