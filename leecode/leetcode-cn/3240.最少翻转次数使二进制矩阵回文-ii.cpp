/*
 * @lc app=leetcode.cn id=3240 lang=cpp
 *
 * [3240] 最少翻转次数使二进制矩阵回文 II
 */

// @lc code=start
class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        int ans = 0;
        for (int i = 0; i < m / 2; ++i) {
            for (int j = 0; j < n / 2; ++j) {
                int cnt = grid[i][j] + grid[m - 1 - i][j] + grid[i][n - 1 - j] + grid[m - 1 - i][n - 1 - j];
                ans += min(cnt, 4 - cnt);
            }
        }

        int cnt1 = 0, diff = 0;
        if (m & 1) {
            int i = m / 2;
            for (int j = 0; j < n / 2; ++j) {
                if (grid[i][j] == grid[i][n - 1 - j]) {
                    cnt1 += grid[i][j] * 2;  // 对称相等的1的个数
                } else {
                    ++diff;  // 对称不等的对数
                }
            }
        }

        if (n & 1) {
            int j = n / 2;
            for (int i = 0; i < m / 2; ++i) {
                if (grid[i][j] == grid[m - 1 - i][j]) {
                    cnt1 += grid[i][j] * 2;
                } else {
                    ++diff;
                }
            }
        }

        // 最少要将 diff 对都翻转一次
        ans += diff;
        if (diff == 0) {
            // 如果cnt1能被4整除，那么将所有的diff都变成0即可，不需要额外翻转；
            // 如果cnt1不能被4整除，那么余数必然为2（因为1成对出现，所以1的个数为偶数）：
            // (1) 如果diff不为0，那么将其中一对diff翻转成1即可，不需要额外翻转；
            // (2) 如果diff为0，那么只能将cnt1中的一个对称对翻转为0，翻转次数加上2（即cnt1除以4的余数）。
            ans += cnt1 % 4;
        }
        if ((m & 1) && (n & 1)) {
            ans += grid[m / 2][n / 2];
        }

        return ans;
    }
};
// @lc code=end
