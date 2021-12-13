// 每个方向上的最高点之间的最小值，决定当前位置可以填充的高度
class Solution {
public:
    int maxIncreaseKeepingSkyline(vector<vector<int>>& grid) {
        if(grid.empty() || grid[0].empty()) return -1;
        int m = grid.size(), n = grid[0].size();
        vector<int> x(m, 0), y(n, 0); // direction：东西方向相同，南北方向相同

        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                x[i] = max(x[i], grid[i][j]); // 东西方向的最高点
                y[j] = max(y[j], grid[i][j]); // 南北方向的最高点
            }
        }

        int ans = 0;
        for(int i=0;i<m;i++) {
            for(int j=0;j<n;j++) {
                int d = min(x[i], y[j]) - grid[i][j]; // 各个方向上最高点的最小值
                if(d > 0) {
                    ans += d;
                }
            }
        }

        return ans;
    }
};