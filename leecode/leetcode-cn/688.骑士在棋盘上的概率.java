// 动态规划
class Solution {
    public double knightProbability(int n, int k, int row, int column) {
        // dp[m][i][j] 表示从 (i,j) 出发，经过 m 步还留在棋盘上的概率
        // 特别地，如果 (i,j) 在棋盘上，那么 dp[0][i][j] = 1
        double[][][] dp = new double[k+1][n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dp[0][i][j] = 1;
        int[][] dirs = {{-1, -2}, {1, -2}, {-2, -1}, {2, -1},
        {-1, 2}, {-2, 1}, {1, 2}, {2, 1}};

        for (int m = 1; m <= k; m++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int[] dir : dirs) {
                        int x = i + dir[0], y = j + dir[1];
                        if (x >= 0 && x < n && y >= 0 && y < n) {
                            dp[m][i][j] += dp[m - 1][x][y] / 8;
                        }
                    }
                }
            }
        }

        return dp[k][row][column];
    }
}