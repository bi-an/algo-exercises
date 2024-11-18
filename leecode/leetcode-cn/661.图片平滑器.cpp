/*
 * @Author: your name
 * @Date: 2022-03-26 17:13:04
 * @LastEditTime: 2022-03-26 17:14:29
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\661.图片平滑器.cc
 */

// 二维前缀和。具体参见 “304. 二维区域和检索 - 矩阵不可变”
class Solution {
    vector<vector<long>> preSum;
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
        int m = img.size(), n = img[0].size();
        if (m == 1 && n == 1)
            return img;
        preSum.resize(m + 1, vector<long>(n + 1, 0));
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                preSum[i][j] = preSum[i-1][j] + preSum[i][j-1] - preSum[i-1][j-1] + img[i - 1][j - 1];
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // (a,b), (c,d) 分别为左上角和右下角
                int a = max(i - 1, 0), b = max(j - 1, 0);
                int c = min(i + 1, m - 1), d = min(j + 1, n - 1);
                int cnt = (c - a + 1) * (d - b + 1);
                ans[i][j] = (preSum[c+1][d+1] - preSum[a][d+1] - preSum[c+1][b] + preSum[a][b]) / cnt;
            }
        }
        return ans;
    }
};