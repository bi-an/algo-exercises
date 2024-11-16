/*
 * @lc app=leetcode.cn id=3239 lang=cpp
 *
 * [3239] 最少翻转次数使二进制矩阵回文 I
 */

// @lc code=start
// 这题只能算简单类型。
// 题解：https://leetcode.cn/problems/minimum-number-of-flips-to-make-binary-grid-palindromic-i/solutions/2868250/fen-bie-ji-suan-pythonjavacgo-by-endless-771t
class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        int ans1 = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                if (grid[i][j] != grid[i][n - 1 - j])
                    ++ans1;
            }
        }

        int ans2 = 0;
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i < m / 2; ++i) {
                if (grid[i][j] != grid[m - 1 - i][j])
                    ++ans2;
            }
        }

        return min(ans1, ans2);
    }
};
// @lc code=end
