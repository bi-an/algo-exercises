/**

可以用字符串表示一个学生的出勤记录，其中的每个字符用来标记当天的出勤情况（缺勤、迟到、到场）。记录中只含下面三种字符：
'A'：Absent，缺勤
'L'：Late，迟到
'P'：Present，到场
如果学生能够 同时 满足下面两个条件，则可以获得出勤奖励：

按 总出勤 计，学生缺勤（'A'）严格 少于两天。
学生 不会 存在 连续 3 天或 连续 3 天以上的迟到（'L'）记录。
给你一个整数 n ，表示出勤记录的长度（次数）。请你返回记录长度为 n 时，可能获得出勤奖励的记录情况 数量 。答案可能很大，所以返回对 10^9 + 7 取余 的结果。

 

示例 1：
输入：n = 2
输出：8
解释：
有 8 种长度为 2 的记录将被视为可奖励：
"PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL" 
只有"AA"不会被视为可奖励，因为缺勤次数为 2 次（需要少于 2 次）。

示例 2：
输入：n = 1
输出：3

示例 3：
输入：n = 10101
输出：183236316
 

提示：

1 <= n <= 10^5

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/student-attendance-record-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/* 官方题解
方法一：动态规划
可以使用动态规划计算可奖励的出勤记录的数量。

由于可奖励的出勤记录要求缺勤次数少于 22 和连续迟到次数少于 33，因此动态规划的状态由总天数、缺勤次数和结尾连续迟到次数决定（由于不会记录连续迟到次数等于或多于 33 的情况，因此非结尾的连续迟到次数一定少于 33，只需要记录结尾连续迟到次数即可）。

定义 dp[i][j][k] 表示前 i 天有 j 个 ‘A’ 且结尾有连续 k 个 ‘L’ 的可奖励的出勤记录的数量，其中 0≤i≤n，0≤j≤1，0≤k≤2。

    当 i=0 时，没有任何出勤记录，此时 ‘A’ 的数量和结尾连续 ‘L’ 的数量一定是 0，因此动态规划的边界情况是 dp[0][0][0]=1。

    当 1≤i≤n 时，dp[i][][] 的值从 dp[i−1][][] 的值转移得到，计算每个状态的值需要考虑第 i 天的出勤记录：

如果第 i 天的出勤记录是 ‘P’，则前 i 天和前 i−1 天的出勤记录相比，‘A’ 的数量不变，结尾连续 ‘L’ 的数量清零，因此对 0≤j≤1，有
    dp[i][j][0] := dp[i][j][0] + sum{dp[i-1][j][k], 0≤k≤2}

如果第 i 天的出勤记录是 ‘A’，则前 i 天和前 i-1 天的出勤记录相比，‘A’ 的数量加 11，结尾连续 ‘L’ 的数量清零，此时要求前 i−1 天的出勤记录记录中的 ‘A’ 的数量必须为 0，否则前 i 天的出勤记录至少有 2 个 ‘A’，不满足可奖励的条件，因此有
    dp[i][1][0] := dp[i][1][0] + sum{dp[i-1][0][k], 0≤k≤2}

如果第 i 天的出勤记录是 ‘L’，则前 ii 天和前 i-1 天的出勤记录相比，‘A’ 的数量不变，结尾连续 ‘L’ 的数量加 11，此时要求前 i−1 天的出勤记录记录中的结尾连续 ‘L’ 的数量不超过 1，否则前 i 天的出勤记录的结尾至少有 3 个 ‘L’，不满足可奖励的条件，因此对 0≤j≤1 和 1≤k≤2，有
    dp[i][j][k] := dp[i][j][k] + dp[i-1][j][k-1]

上述状态转移方程对于 i=1 也适用。

计算长度为 nn 的所有可奖励的出勤记录的数量，即为计算 dp[n][][] 的所有元素之和。计算过程中需要将结果对 10^9+7 取模。

根据上述思路，可以得到时间复杂度和空间复杂度都是 O(n) 的实现。

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/student-attendance-record-ii/solution/xue-sheng-chu-qin-ji-lu-ii-by-leetcode-s-kdlm/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = (int)(1e9 + 7);
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
        dp[0][0][0] = 1;
        int ans = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 3; k++) {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j][k]) % MOD;
                    if(j > 0) dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][k]) % MOD;
                    // 注意：这里不能再加上dp[i][j][k - 1]，因为按照本题分类讨论的思路，dp[i][][]只能由dp[i-1][][]推导出来，
                    // 如果再加上dp[i][j][k - 1]，会引入重复计算
                    if(k > 0) dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k - 1]) % MOD;// +dp[i][j][k - 1];
                }
            }
        }

        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 3; k++) {
                ans = (ans + dp[n][j][k]) % MOD;
            }
        }

        return ans;
    }
};

// 状态压缩
// TODO 时间复杂度也优化了4倍左右，为什么呢？
class Solution {
public:
    int checkRecord(int n) {
        const int MOD = (int)(1e9 + 7);
        vector<vector<int>> dp(2, vector<int>(3, 0)), cur = dp;
        dp[0][0] = 1;
        int ans = 0;
        for(int i=1;i<=n;i++) {
            zero(cur);
            for(int j=0;j<2;j++) {
                for(int k=0;k<3;k++) {
                    cur[j][0] = (cur[j][0] + dp[j][k]) % MOD;
                    if(j > 0) cur[j][0] = (cur[j][0] + dp[j-1][k]) % MOD;
                    if(k > 0) cur[j][k] = (cur[j][k] + dp[j][k-1]) % MOD;
                }
            }
            dp = cur;
        }

        for(int j=0;j<2;j++) {
            for(int k=0;k<3;k++) {
                ans = (ans + dp[j][k]) % MOD;
            }
        }

        return ans;
    }

    void zero(vector<vector<int>>& vec) {
        for(int i=0;i<vec.size();i++) {
            for(int j=0;j<vec[0].size();j++)
                vec[i][j] = 0;
        }
    }
};