/*
 * @lc app=leetcode.cn id=712 lang=cpp
 *
 * [712] 两个字符串的最小ASCII删除和
 */

// @lc code=start
// 注意：这题仅仅删除字符，不能改变字符，它不是最小编辑距离，
// 所有不同的字符都应该删除，对于相同的字符，删除哪个位置上的都是一样的。
// s1和s2从最后一个字符开始比较，
// dp[i][j]表示s1[end]到s1[i]为止、s2[end]到s2[j]为止，删去的字符ascii和。
// s1:      i
//	   ---------------------------
//	   | | | | | | | | | | | | | |
//     ---------------------------
// s2:				j
//     ---------------------------
//     | | | | | | | | | | | | | |
//     ---------------------------
// 如图：dp二维表格，填dp[i][j]时，若s1[i]==s2[j]，则应该直接跳过这两个字符，即dp[i][j]=dp[i+1][j+1];
// 若s1[i]!=s2[j]，则应该选择删除s1[i]还是删除s2[j]，若删除s1[i]则表示留下的是s1[i+1]和s2[j]，即dp[i][j]=dp[i+1][j]；若删除s2[j]类似。
// 初始化：dp[m][n]表示s1和s2都为空，所以初始化为0；
// dp[i][n]表示留下的s2含有0个字符，所以应该把s1部分全部删掉，所以dp[i][n]是所有s1的acsii加起来；dp[m][j]类似。

// 时间复杂度: O(m*n)
// 空间复杂度: O(m*n)
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[m][n] = 0;  // s1与s2都为空
        for (int i = m - 1; i >= 0; i--)
            dp[i][n] = dp[i + 1][n] + s1[i];  // s2为空
        for (int j = n - 1; j >= 0; j--)
            dp[m][j] = dp[m][j + 1] + s2[j];  // s1为空

        for (int i = m - 1; i >= 0; i--)
            for (int j = n - 1; j >= 0; j--) {
                if (s1[i] != s2[j])
                    dp[i][j] = std::min(dp[i + 1][j] + s1[i], dp[i][j + 1] + s2[j]);  // 删除s1[i]，则dp[i][j]=dp[i+1][j]+s1[i];
                                                                                      // 删除s2[j]，则dp[i][j]=dp[i][j+1]+s2[j]
                else
                    dp[i][j] = dp[i + 1][j + 1];  // s1[i]==s2[j]，跳过这两个字符
            }
        return dp[0][0];
    }
};

namespace solution_2 {
// 时间复杂度: O(m*n)
// 空间复杂度: O(n)
class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        vector<int> dp(n + 1);
        dp[n] = 0;
        for (int j = n - 1; j >= 0; j--)
            dp[j] = dp[j + 1] + s2[j];
        int temp = 0, dialog = 0;  // temp为dp[i+1][j+1]

        for (int i = m - 1; i >= 0; i--) {
            dialog += s1[i];
            dp[n] = dialog;  // dp[n]为dp[i][n]
            for (int j = n - 1; j >= 0; j--)
                if (s1[i] == s2[j]) {
                    int tm = dp[j];
                    dp[j] = temp;
                    temp = tm;
                } else {
                    temp = dp[j];
                    dp[j] = std::min(s1[i] + dp[j], s2[j] + dp[j + 1]);  // 等式左边dp[j]为dp[i][j]，等式右边dp[j]为dp[i+1][j]
                }
            temp = dialog;  // temp为dp[i+1][j+1]
        }
        return dp[0];
    }
};
}  // namespace solution_2
// @lc code=end
