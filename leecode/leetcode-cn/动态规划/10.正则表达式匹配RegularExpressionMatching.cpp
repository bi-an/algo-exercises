// 方法一：递归
// 时间复杂度：O(n^2)
// 空间复杂度：O(n^2)
class Solution {
public:
    bool isMatch(string s, string p) {
        return dfs(s, 0, p, 0);
    }

    bool dfs(string& s, int i, string& p, int j) {
        if (j >= p.length())
            return i >= s.length();
        
        bool first_match = i < s.length() && (s[i] == p[j] || p[j] == '.');

        if (j + 1 < p.length() && p[j + 1] == '*') {
            return dfs(s, i, p, j + 2) || first_match && dfs(s, i + 1, p, j);
        }
        else {
            return first_match && dfs(s, i + 1, p, j + 1);
        }
    }
};

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
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1)); // 默认初始化为 false
        dp[0][0] = true; // 如果 s 和 p 长度都为 0，那么认为是匹配的
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
                    // 注意：dp[i - 1][j] 中，只能后退 i，不能后退 j 为 j - 1 或 j - 2，
                    // 因为 * 可能匹配 0 次或多次。
                    // 如果后退 j，则 后退为 j - 1 表示 * 匹配了 1 次，后退为 j - 2 表示 * 匹配了 0 次，
                    // 但是 * 匹配多次的情况，需要改为 i - k, j - 1，其中 k 为 * 匹配的次数，这样太复杂了。
                    // 如果后退 i，上述情况都已经包括了，讨论起来简单很多。
                    dp[i][j] = dp[i][j - 2] || (isMatch(i - 1, j - 2) && dp[i - 1][j]);
                } else {
                    dp[i][j] = isMatch(i - 1, j - 1) && dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};
