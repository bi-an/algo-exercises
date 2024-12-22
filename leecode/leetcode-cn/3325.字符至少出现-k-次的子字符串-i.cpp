/*
 * @lc app=leetcode.cn id=3325 lang=cpp
 *
 * [3325] 字符至少出现 K 次的子字符串 I
 */

// @lc code=start
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int ans = 0, n = s.length(), m = 0;
        int cnt[128]{};
        for (int l = 0, r = 0; r < n; ++r) {
            if (++cnt[s[r]] == k)
                ++m;
            // 先找最小区间
            while (l <= r && m >= 1)
                m -= cnt[s[l++]]-- == k;
            ans += l;
        }
        return ans;
    }
};
// @lc code=end

// 更简洁的写法
namespace version_2 {

class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int ans = 0, n = s.length();
        int cnt[128]{};
        for (int l = 0, r = 0; r < n; ++r) {
            ++cnt[s[r]];
            // 先找最小区间
            // left 始终指向合法区间左端点的下一个位置，
            // 所以上次区间必然是不合法的，如果此次合法，就必然是 s[right] 导致的。
            // left 不可能越界，因为 cnt[s[left]] 最小为 k-1 .
            while (cnt[s[r]] >= k)
                --cnt[s[l++]];
            ans += l;
        }
        return ans;
    }
};

}  // namespace version_2
