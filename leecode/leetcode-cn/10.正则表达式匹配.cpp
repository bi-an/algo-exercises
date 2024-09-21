/*
 * @lc app=leetcode.cn id=10 lang=cpp
 *
 * [10] 正则表达式匹配
 */

// @lc code=start
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();

        // s[i] 与 p[j] 是否匹配
        auto matches = [&](int i, int j) -> bool {
            return s[i] == p[j] || p[j] == '.';
        };

        // dp[i][j] 表示长度为 i 的字符串与长度为 j 的模式串是否匹配
        // 相比 bool ，使用 int 能够更好地字节对齐，使得 CPU 运行更快
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;

        for (int i = 0; i <= m; ++i) {
            // 如果模式串长度为 0 ，那么一定不匹配，
            // 所以 j=0 时，dp[i][0]=false
            for (int j = 1; j <= n; ++j) {
                // 长度至少为 2 ，'*' 才能用于匹配
                if (j >= 2 && p[j - 1] == '*') {
                    // (1) "x*" 匹配 0 次
                    // 此时只需要 s[0,...,i-1] 与 p[0,...,j-3] 匹配就可以了。
                    // (2) "x*" 匹配多于 0 次
                    // 其中 dp[i-1][j] 可以表示s[0,...,i-2] 与 p[0,...,j-1] 匹配的所有情况，包括 * 匹配 0 次或多次。
                    dp[i][j] = dp[i][j - 2] || i - 1 >= 0 && matches(i - 1, j - 2) && dp[i - 1][j];
                } else {
                    // s[i-1]=p[j-1] 时
                    dp[i][j] = i - 1 >= 0 && matches(i - 1, j - 1) && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};

namespace solution_2 {
// 方法一：递归
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)
class Solution {
public:
    bool isMatch(string s, string p) {
        return dfs(s, 0, p, 0);
    }

    bool dfs(string& s, int i, string& p, int j) {
        // 注意，这里是先判断 p 的下标是否越界。
        // 因为存在如下情况：
        // s: abcdddd
        // p: abcd*
        // 当 s 遍历完，但是 p 的指针还是指向 d.
        if (j >= p.length())
            return i >= s.length();

        // 如果 p 没有访问完、s 已经访问完了，此时 first_match = false.
        // 但是这不意味着答案就是 false，因为 a* 可以出现 0 次。
        bool first_match = i < s.length() && (s[i] == p[j] || p[j] == '.');

        if (j + 1 < p.length() && p[j + 1] == '*') {
            return dfs(s, i, p, j + 2) || first_match && dfs(s, i + 1, p, j);
        } else {
            return first_match && dfs(s, i + 1, p, j + 1);
        }
    }
};

}  // namespace solution_2

namespace solution_3 {
// 方法二：动态规划
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length(), n = p.length();

        // lamdba 表达式：判断 s[i] 与 p[j] 是否匹配。
        auto isMatch = [&](int i, int j) {
            if (j >= n)
                return i >= n;
            return i >= 0 && i < m && (s[i] == p[j] || p[j] == '.');
        };

        // 动态规划
        // dp[i][j] 表示长度为 i 的字符串 s 与 长度为 j 的模式串 p 是否能够匹配。
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));  // 默认初始化为 false
        dp[0][0] = true;                                      // 如果 s 和 p 长度都为 0，那么认为是匹配的
        // s = "", p = "x*"，应该认为是匹配的。
        // dp[i][0] = false.
        // 循环中的 i, j 表示长度
        for (int i = 0; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (j >= 2 && p[j - 1] == '*') {
                    // (1)"x*" 被匹配了 0 次，其中 x 表示任意字母。
                    // 如果 s[0...i-1] 与 p[0...j-1] 能匹配，
                    // 当且仅当 s[0...i-1] 与 p[0...j-3] 能匹配。
                    // (2)"x*" 被匹配了 1 次。
                    // 由于我们是递推，所以，匹配多次的情况可以在之后继续匹配 0 次或 1 次。
                    // 注意：dp[i - 1][j] 中，只能后退 i，不能后退 j，
                    // 因为 * 可能匹配 0 次或多次。
                    // 如果后退 j，则 后退为 j - 1 表示 * 匹配了 1 次，后退为 j - 2 表示 * 匹配了 0 次，
                    // 但是 * 匹配多次的情况，需要改为 i - k, j - 1，其中 k 为 * 匹配的次数，这样太复杂了。
                    // 如果后退 i，上述情况都已经包括了，讨论起来简单很多。
                    // dp[i-1][j] 可以表示s[0,...,i-2] 与 p[0,...,j-1] 匹配的所有情况，包括 * 匹配 0 次或多次。
                    dp[i][j] = dp[i][j - 2] || (isMatch(i - 1, j - 2) && dp[i - 1][j]);
                } else {
                    dp[i][j] = isMatch(i - 1, j - 1) && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};
}  // namespace solution_3

// @lc code=end
