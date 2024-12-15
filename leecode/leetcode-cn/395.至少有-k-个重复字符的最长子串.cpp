/*
 * @lc app=leetcode.cn id=395 lang=cpp
 *
 * [395] 至少有 K 个重复字符的最长子串
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
// 方法一：遍历字符种类 + 滑动窗口
// 官方题解：https://leetcode.cn/problems/longest-substring-with-at-least-k-repeating-characters/solutions/623432/zhi-shao-you-kge-zhong-fu-zi-fu-de-zui-c-o6ww/
// 时间复杂度：O(|Σ|·(n + |Σ|)) = O(n·|Σ|+|Σ|²)
// 空间复杂度：O(|Σ|)
class Solution {
public:
    int longestSubstring(string s, int k) {
        int ans = 0, n = s.length();
        // 假设满足条件的字符串中一共只有 t 种字符，枚举所有种类数
        for (int t = 1; t <= 26; ++t) {
            int total = 0;        // 种类数
            int less = 0;         // 出现次数小于 k 的字符种类
            vector<int> cnt(26);  // 初始化的时间复杂度为 O(|Σ|)
            for (int l = 0, r = 0; r < n; ++r) {
                // 记录 less 和 total
                if (cnt[s[r] - 'a']++ == 0) {
                    ++total;
                    ++less;
                }
                if (cnt[s[r] - 'a'] == k)
                    --less;
                // 右移左端点，直到窗口内字符种类数 ≤ t
                while (total > t) {
                    if (cnt[s[l] - 'a'] == k)
                        ++less;
                    if (--cnt[s[l++] - 'a'] == 0) {
                        --total;
                        --less;
                    }
                }
                if (less == 0)  // 窗口内所有字符出现次数都 ≥ k
                    ans = max(ans, r - l + 1);
            }
        }
        return ans;
    }
};
// @lc code=end

// 方法二：分治法
// 对于给定字符串，找出一个不符合条件的字符，则合法子串被该字符分割成更小的子串。
// 然后对该子串再次重复以上操作，直至子串长度为 0 。
// 分治过程中记录最长合法子串长度。
// 时间复杂度：O(n·|Σ|)，由于每次分治找出的非法字符必然不同，所以分治层数最大为 |Σ| 。
// 空间复杂度：O(|Σ|²)，最大递归深度为 |Σ| ，每次需要开辟 |Σ| 的空间。
namespace solution_2 {

// FIXME
class Solution {
    int dfs(string& s, int l, int r, int k) {
        vector<int> cnt(26);
        for (char c : s)
            ++cnt[c - 'a'];
        // 找到第一个非法字符
        char ill = 0;  // illegal char
        for (int i = 0; i < 26; ++i) {
            // 出现过，但是出现次数少于 k
            if (cnt[i] && cnt[i] < k) {
                ill = i + 'a';
                break;
            }
        }
        if (ill == 0)
            return r - l + 1;
        // 分割
        int i = l, maxLen = 0;
        while (i <= r) {
            while (i <= r && s[i] == ill)
                i++;
            int j = i;
            while (j <= r && s[j] != ill)
                j++;
            maxLen = max(maxLen, dfs(s, i, j - 1, k));
            i = j;
        }
        return maxLen;
    };

public:
    int longestSubstring(string s, int k) {
        return dfs(s, 0, s.length() - 1, k);
    }
};

}  // namespace solution_2

int main() {
    string s = "bbaaacbd";
    int k = 3;
    Solution sol;
    int ans = sol.longestSubstring(s, k);
    cout << ans << endl;

    return 0;
}