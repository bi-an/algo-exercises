/*
 * @Author: your name
 * @Date: 2021-08-25 22:38:42
 * @LastEditTime: 2021-08-26 00:17:27
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\787.K站中转内最便宜的航班.cc
 */

/**
 * 有 n 个城市通过一些航班连接。给你一个数组 flights ，其中 flights[i] = [fromi, toi, pricei] ，表示该航班都从城市 fromi 开始，以价格 pricei 抵达 toi。

现在给定所有的城市和航班，以及出发城市 src 和目的地 dst，你的任务是找到出一条最多经过 k 站中转的路线，使得从 src 到 dst 的 价格最便宜 ，并返回该价格。 如果不存在这样的路线，则输出 -1。


示例 1：

输入: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 1
输出: 200
解释: 
城市航班图如下


从城市 0 到城市 2 在 1 站中转以内的最便宜价格是 200，如图中红色所示。
示例 2：

输入: 
n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
src = 0, dst = 2, k = 0
输出: 500
解释: 
城市航班图如下


从城市 0 到城市 2 在 0 站中转以内的最便宜价格是 500，如图中蓝色所示。
 

提示：

1 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
航班没有重复，且不存在自环
0 <= src, dst, k < n
src != dst

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/cheapest-flights-within-k-stops
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 */

// @Athor zzg
// 动态规划
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        const int MAX_COST = 10000 * 101 + 1; // 根据题意的取值范围，最多经过k+1条边
        vector<vector<int>> adj(n,vector<int>(n, MAX_COST));
        vector<vector<int>> dp(k+2, vector<int>(n, MAX_COST));
        // dp[t][i]表示从src出发最多经过t条边到达i的最少花费

        for(vector<int>& flight : flights) {
            int from = flight[0], to = flight[1], price = flight[2];
            adj[from][to] = price;
        }
        for(int i=0;i<n;i++) {
            adj[i][i] = 0;
        }

        dp[0][src] = 0;

        for(int t=1;t<=k+1;t++) {
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    dp[t][i] = min(dp[t][i], dp[t-1][j] + adj[j][i]);
                }
            }
        }

        return dp[k+1][dst] == MAX_COST ? -1 : dp[k+1][dst];
    }
};

// 空间优化：没有必要保存邻接矩阵，访问邻接矩阵本质上就是遍历航班（边），这样空间能优化1倍左右
// TODO 实际测试时，空间仅仅优化了0.1~0.2 MB左右
// 时间优化：既然没有邻接矩阵，相当于只遍历了一次航班，时间上大概能够优化1倍左右
// 这实际上是Bellman-Ford算法的变体（或说应用），时间复杂度为|V|·|E|，其中|V|为顶点个数，|E|为边条数
class Solution {
    static constexpr int INF = 10000 * 101 + 1;
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> dp(k+2, vector<int>(n, INF));
        dp[0][src] = 0;
        int ans = INF;

        for(int t=1;t<=k+1;t++) {
            for(vector<int>& flight : flights) {
                int from = flight[0], to = flight[1], price = flight[2];
                dp[t][to] = min(dp[t][to], dp[t-1][from] + price);
            }
        }

        // 注意：通过邻接表遍历顶点时，相当于认为本地到本地是有路径的，花费为0，这样可以保持曾经的最优值；
        // 但是，本解法仅仅遍历了边，这时，本地到本地没有航班，所以下一次遍历会冲掉曾经的最优值，
        // 所以还需要再次遍历一次，寻找曾经的最优值。
        // 综上，不同的是，本解法的dp[t][i]表示从src出发“必定”经过t条边到达i的最少花费。
        // 因为每一次遍历边，都必定有航班，所以，从本次循环必定比上一次增加了一次行程，经过的边数是递增的。
        // 题外话：这里t条边不是“实际”经乘的航班数，因为初始化时，我们认为从src经过0条边可达任意一个地点，
        // 所以，之后可以从任意地点再次出发，之后经历的行程数确实从0开始不断递增。
        for(int t=0;t<=k+1;t++)
            ans = min(ans, dp[t][dst]);

        return ans == INF ? -1 : ans; //dp[k+1][dst] == INF ? -1 : dp[k+1][dst];
    }
};