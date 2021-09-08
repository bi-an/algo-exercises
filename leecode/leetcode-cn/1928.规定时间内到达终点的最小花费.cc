// https://leetcode-cn.com/problems/minimum-cost-to-reach-destination-in-time/

// 注意：“图中两个节点之间可能有多条路径”，指不经过第三个节点的路径也不止一条
// 如果使用邻接表遍历，需要注意这一点，创建时邻接表时需要更新为最短的那条路径
// 由于题目的取值范围，不能使用邻接表遍历，会超时
class Solution {
    // 由于题目给出的取值范围，INTY取 1000 * 1000 + 1 也可以
    static constexpr int INTY = INT_MAX / 2; // 保证两个数相加不会超过INT_MAX
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        // dp[i][t]表示从0到达i、用时恰好为t的最小费用
        // 注意：由于我们是对边遍历，所以没法表示“用时不超过t的最小费用”
        vector<vector<int>> dp(n, vector<int>(maxTime + 1, INTY));
        int ans = INTY;

        // Bellman-Ford算法，可以证明，最多经过 V 次遍历所有边，可以求出最短路径
        // 证明过程可以参考《算法导论》
        // 该算法时间复杂度为 O(V*E)，其中V为顶点数，E为边数
        dp[0][0] = passingFees[0];
        for(int t=0;t<=maxTime;t++) {
            for(vector<int>& edge : edges) {
                int i = edge[0], j = edge[1], t1 = edge[2];
                if(t - t1 >= 0) {
                    dp[i][t] = min(dp[i][t], dp[j][t - t1] + passingFees[i]);
                    dp[j][t] = min(dp[j][t], dp[i][t - t1] + passingFees[j]);
                }
            }
        }
        for(int t=0;t<=maxTime;t++) {
            ans = min(ans, dp[n-1][t]);
        }
        return (ans == INTY) ? -1 : ans;
    }
};