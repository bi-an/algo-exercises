/*
 * @lc app=leetcode.cn id=1234 lang=cpp
 *
 * [1234] 替换子串得到平衡字符串
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
// 如果窗口外的字符的计数都 ≤ n/4 ，则一定可以通过替换窗口内的字符串使之合法
class Solution {
public:
    int balancedString(string s) {
        int n = s.length(), ans = n;
        unordered_map<char, int> cnt;
        for (auto c : s)
            ++cnt[c];

        auto check = [&]() {
            const int m = n / 4;
            return cnt['Q'] <= m && cnt['W'] <= m &&
                   cnt['E'] <= m && cnt['R'] <= m;
        };

        if (check())
            return 0;

        // 区间 [left, right)
        for (int l = 0, r = 0; l < n; ++l) {
            while (r <= n && !check()) {
                --cnt[s[r++]];
            }
            if (check())
                ans = min(ans, r - l);
            ++cnt[s[l]];
        }

        return ans;
    }
};
// @lc code=end

int main() {
    string s = "QQQW";
    Solution sol;
    int res = sol.balancedString(s);
    cout << res << endl;

    return 0;
}