/*
 * @lc app=leetcode.cn id=2379 lang=cpp
 *
 * [2379] 得到 K 个黑块的最少涂色次数
 */

// @lc code=start
// 定长滑动窗口
// 即求长度为 k 的滑动窗口中的最少白色块个数
class Solution {
public:
    int minimumRecolors(string blocks, int k) {
        int n = blocks.length(), cnt = 0, min_cnt = INT_MAX;
        for (int i = 0; i < n; ++i) {
            cnt += (blocks[i] == 'W');
            if (i < k - 1)
                continue;
            min_cnt = min(min_cnt, cnt);
            // 下一次
            cnt -= (blocks[i - k + 1] == 'W');
        }
        return min_cnt;
    }
};
// @lc code=end
