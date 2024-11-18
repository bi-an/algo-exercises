/**
 * 给你一个大小为 m x n 的网格和一个球。球的起始坐标为 [startRow, startColumn] 。你可以将球移到在四个方向上相邻的单元格内（可以穿过网格边界到达网格之外）。
 * 你 最多 可以移动 maxMove 次球。

给你五个整数 m、n、maxMove、startRow 以及 startColumn ，找出并返回可以将球移出边界的路径数量。因为答案可能非常大，返回对 10^9 + 7 取余 后的结果。

 

示例 1：


输入：m = 2, n = 2, maxMove = 2, startRow = 0, startColumn = 0
输出：6
示例 2：


输入：m = 1, n = 3, maxMove = 3, startRow = 0, startColumn = 1
输出：12
 

提示：

1 <= m, n <= 50
0 <= maxMove <= 50
0 <= startRow < m
0 <= startColumn < n


来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/out-of-boundary-paths
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

// 动态规划
// dp[i][x][y]表示移动i次到达(x,y)处的路径数
// 按照dp[i]->dp[i+1]更新比较方便，而不是dp[i-1]->dp[i];
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = (int)(1e9+7);
        vector<vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1,0}};
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(m, vector<int>(n, 0)));
        dp[0][startRow][startColumn] = 1;
        int outCount = 0;
        for(int i=0;i<maxMove;i++) {
            for(int x = 0;x<m;x++) {
                for(int y = 0;y<n;y++) {
                    int count = dp[i][x][y];
                    for(auto& direction : directions) {
                        int x1 = direction[0] + x, y1 = direction[1] + y;
                        if(x1 >= 0 && x1 < m && y1 >= 0 && y1 < n) {
                            dp[i+1][x1][y1] = (dp[i+1][x1][y1] + count) % MOD;
                        } else {
                            outCount = (outCount + count) % MOD;
                        }
                    }
                }
            }
        }
        return outCount;
    }
};

// 写法二
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = (int)(1e9+7);
        int ans = 0;
        vector<vector<vector<int>>> dp(maxMove+1,vector<vector<int>>(m,vector<int>(n)));
        dp[0][startRow][startColumn] = 1;

        for(int i=1;i<=maxMove;i++) {
            // printf("i=%d\n",i);
            for(int x=-1;x<=m;x++) {
                // printf("\t");
                for(int y=-1;y<=n;y++) {
                    if((x==-1 || x==m) && (y==-1 || y==n)) continue;

                    if(x==-1) ans = (ans + dp[i-1][x+1][y]) % MOD;
                    else if(x==m) ans = (ans + dp[i-1][x-1][y]) % MOD;
                    else if(y==-1) ans = (ans + dp[i-1][x][y+1]) % MOD;
                    else if(y==n) ans = (ans + dp[i-1][x][y-1]) % MOD;
                    else {
                        if(x > 0) dp[i][x][y] = (dp[i][x][y] + dp[i-1][x-1][y]) % MOD;
                        if(x < m - 1) dp[i][x][y] = (dp[i][x][y] + dp[i-1][x+1][y]) % MOD;
                        if(y > 0) dp[i][x][y] = (dp[i][x][y] + dp[i-1][x][y-1]) % MOD;
                        if(y < n - 1) dp[i][x][y] = (dp[i][x][y] + dp[i-1][x][y+1]) % MOD;
                        // printf("%d ", dp[i][x][y]);
                    }
                }
                // printf("\n");
            }
        }
        return ans;
    }
};

// 状态压缩
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        int outCount = 0;
        const int MOD = (int)(1e9 + 7);
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[startRow][startColumn] = 1;
        vector<vector<int>> directions = {{-1,0}, {1,0}, {0, -1}, {0, 1}};
        for(int i=0;i<maxMove;i++) {
            vector<vector<int>> dpNew(m, vector<int>(n, 0));
            for(int x=0;x<m;x++) {
                for(int y=0;y<n;y++) {
                    int count = dp[x][y];
                    for(auto& direction :　directions) {
                        int x1 = direction[0] + x, y1 = direction[1] + y;
                        if(x1 >= 0 && x1 < m && y1 >= 0 && y1 < n) {
                            dpNew[x1][y1] = (dpNew[x1][y1] + count) % MOD;
                        } else {
                            outCount = (outCount + count) % MOD;
                        }
                    }
                }
            }
            dp = dpNew;
        }
        return outCount;
    }
};

// 状态压缩写法二
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        const int MOD = (int)(1e9+7);
        vector<vector<int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1,0}};
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(n, 0)));
        dp[0][startRow][startColumn] = 1;
        int outCount = 0;
        // printf("Solution2\n");
        for(int i=0;i<maxMove;i++) {
            // printf("i=%d\n",i);
            for(int x = 0;x<m;x++) {
                // printf("\t");
                for(int y = 0;y<n;y++) {
                    int count = dp[i % 2][x][y];
                    // printf("%d ", count);
                    for(auto& direction : directions) {
                        int x1 = direction[0] + x, y1 = direction[1] + y;
                        if(x1 >= 0 && x1 < m && y1 >= 0 && y1 < n) {
                            dp[(i+1)%2][x1][y1] = (dp[(i+1)%2][x1][y1] + count) % MOD;
                        } else {
                            outCount = (outCount + count) % MOD;
                        }
                    }
                }
                // printf("\n");
            }
            for(vector<int>& vec : dp[i%2]) {
                vec.assign(vec.size(), 0);
            }
        }
        return outCount;
    }
};