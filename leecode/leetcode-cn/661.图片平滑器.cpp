/*
 * @lc app=leetcode.cn id=661 lang=cpp
 *
 * [661] 图片平滑器
 */

// @lc code=start
// 二维前缀和。具体参见 “304. 二维区域和检索 - 矩阵不可变”
class Solution {
    vector<vector<long>> preSum;

public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size(), n = img[0].size();
        // if (m == 1 && n == 1)
        //     return img;
        preSum.resize(m + 1, vector<long>(n + 1, 0));
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1] + img[i - 1][j - 1];
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // (a,b), (c,d) 分别为左上角和右下角
                int a = max(i - 1, 0), b = max(j - 1, 0);
                int c = min(i + 1, m - 1), d = min(j + 1, n - 1);
                int cnt = (c - a + 1) * (d - b + 1);
                ans[i][j] = (preSum[c + 1][d + 1] - preSum[a][d + 1] - preSum[c + 1][b] + preSum[a][b]) / cnt;
            }
        }
        return ans;
    }
};
// @lc code=end
