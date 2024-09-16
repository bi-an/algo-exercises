// 题解：https://leetcode.cn/problems/maximum-multiplication-score/solutions/2917840/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-9ul8/
// 动态规划一般有两种寻找递推式的方法：选或不选；枚举哪个。
class Solution {
public:
    long long maxScore(vector<int> &a, vector<int> &b) {
        int n = b.size();
        // dp[i][j] 表示从b[0],...,b[i]中选j+1个，来与a[0],...,a[j]匹配的计算结果
        // 分类讨论：
        // (1)不选b[i]：从b[0],...,b[i-1]中选j+1个 => dp[i][j]=dp[i-1][j]
        // (2)选b[i]：从b[0],...,b[i-1]中选j个 => dp[i][j]=dp[i-1][j-1] + b[i] * a[j]
        // 选二者的最大值。
        // 我们观察到，dp的下标是有意义的，
        // 此时dp[-1][j]表示b序列长度为0；dp[i][-1]表示b序列中一个都没有选。
        // 为了防止dp的下标越界，我们直接将每一项都后移一位，
        // 也就是将上面递推式中的dp的下标都加1，见下面的代码（注意b[i]和a[j]不需要改）
        vector<array<long long, 5>> dp(n + 1);

        // 初始化
        // 观察递推式，我们只关注当前格子的左对角线和上方的格子，
        // 所以只需要初始化第一行；第一列中我们只关注第一个（被第一行包括了）。
        ranges::fill(dp[0].begin() + 1, dp[0].end(), LLONG_MIN / 2);  // 防止加法溢出
        dp[0][0] = 0;                                                 // 这一步很关键，决定递推式中dp[i][j] + (long long)b[i] * a[j]的结果

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 4; ++j) {
                dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i][j] + (long long)b[i] * a[j]);
            }
        }

        return dp[n][4];
    }
};

// 也可以使用“递归+记忆化搜索（也就是记录已经遍历的情况，避免重复遍历）”的方法。
// 原理与动态规划类似，只是倒过来遍历
