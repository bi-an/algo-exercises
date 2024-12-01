/*
 * @lc app=leetcode.cn id=2953 lang=cpp
 *
 * [2953] 统计完全子字符串
 */

// @lc code=start
// 题解：https://leetcode.cn/problems/count-complete-substrings/solutions/2551743/bao-li-hua-chuang-mei-ju-chuang-kou-nei-31j5m/
// 化整为零：
// 先根据条件2分割原字符串，每次找出满足条件2的最长子串；
// 再根据条件1，枚举 26 种字符，即每次枚举假定窗口内共有 m （1~26）种字符，应该使用 m*k 长度的滑动窗口，判断窗口内的字符是否满足条件1 。
//
// 时间复杂度：O(n|Σ|²) ，其中 |Σ| = 26 表示字符集的大小，
// 推导：首先分割字符串；针对每个子串，每个字符（共 26 种）都用滑动窗口遍历了一次；但是每次使用滑动窗口遍历时，check() 函数又花费 |Σ| 的时间。
class Solution {
    // 枚举并判断条件1
    int f(string_view s, int k) {
        int res = 0, n = s.length();
        // 枚举 26 种字符
        for (int m = 1; m <= 26; ++m) {
            int cnt[26]{};  // 列表初始化
            // 检查窗口内的字符计数
            auto check = [&]() {
                for (int i = 0; i < 26; ++i) {
                    if (cnt[i] && cnt[i] != k)
                        return;
                }
                ++res;  // 合法
            };
            // 定长 m*k 的滑动窗口
            for (int right = 0; right < n; ++right) {
                // 右端点
                cnt[s[right] - 'a']++;
                // 左端点
                int left = right + 1 - m * k;
                if (left >= 0) {
                    check(); // 时间复杂度 O(|Σ|)
                    // 为下次作准备
                    cnt[s[left] - 'a']--;
                }
            }
        }
        return res;
    }

public:
    int countCompleteSubstrings(string word, int k) {
        int ans = 0, n = word.length();
        string_view s(word);  // (C++17) string_view 的 substr 不会深度复制

        // 每次找出满足条件2的最长子串
        for (int i = 0; i < n;) {
            int st = i;  // start
            // 当前最长的满足条件2 的子串
            for (i++; i < n && abs(int(word[i]) - int(word[i - 1])) <= 2; i++)
                ;
            ans += f(s.substr(st, i - st), k);
        }

        return ans;
    }
};
// @lc code=end


// TODO: 优化时间复杂度为 O(n|Σ|)