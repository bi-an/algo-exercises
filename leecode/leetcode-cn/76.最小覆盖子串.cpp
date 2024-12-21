/*
 * @lc app=leetcode.cn id=76 lang=cpp
 *
 * [76] 最小覆盖子串
 */

namespace solution_1 {

class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length();
        // unordered_map<char, int> cnt_s, cnt_t;
        int cnt_s[128]{}, cnt_t[128]{};  // ASCII 共 128 个字符

        // m 记录 t 中还有多少个字符没有从 s 中抵消
        int m = 0;
        for (auto c : t) {
            if (cnt_t[c] == 0)
                ++m;
            ++cnt_t[c];
        }

        int ans_l = 0, ans_r = n;  // m = cnt_t.size();
        for (int l = 0, r = 0; r < n; ++r) {
            m -= ++cnt_s[s[r]] == cnt_t[s[r]];
            // 一旦从 s 中找到 t 中的字符，除非其个数超出，否则将一直保持在窗口内
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

}  // namespace solution_1

// @lc code=start
// 写法二：和写法一相同，这次只使用一个哈希表，定义 cnt[i] = cnt_t[i] - cnt_s[i] 。
class Solution {
public:
    string minWindow(string s, string t) {
        int n = s.length(), ans_l = 0, ans_r = n;

        int cnt[128]{}, m = 0;
        for (auto c : t) {
            if (cnt[c] == 0)
                m++;
            ++cnt[c];
        }

        for (int l = 0, r = 0; r < n; ++r) {
            if (cnt[s[r]]-- > 0 && cnt[s[r]] == 0)
                --m;
            // 不需要考虑 s[i] 在 t 中有没有，因为其刚开始是正值，只有该字符个数超过 t 中的个数时，
            // 才会变成负值。而我们一旦增加到 0 就停止了，也就是恢复到刚刚与 t 中抵消即止。
            // 换言之，t 中的字符一旦在 s 中出现，就不会再脱离窗口，除非个数超出。
            while (l <= r && cnt[s[l]] < 0)
                ++cnt[s[l++]];
            if (m == 0 && ans_r - ans_l > r - l) {
                ans_l = l;
                ans_r = r;
            }
        }
        return ans_r < n ? s.substr(ans_l, ans_r - ans_l + 1) : "";
    }
};
// @lc code=end
