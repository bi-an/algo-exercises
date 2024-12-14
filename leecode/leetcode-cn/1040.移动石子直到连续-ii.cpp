/*
 * @lc app=leetcode.cn id=1040 lang=cpp
 *
 * [1040] 移动石子直到连续 II
 */

// @lc code=start
// 题解：https://leetcode.cn/problems/moving-stones-until-consecutive-ii/solutions/2212638/tu-jie-xia-tiao-qi-pythonjavacgo-by-endl-r1eb/
// 官方题解：https://leetcode.cn/problems/moving-stones-until-consecutive-ii/solutions/2211189/yi-dong-shi-zi-zhi-dao-lian-xu-ii-by-lee-8u5g/

// 端点石子只能向中心移动，那么每次移动后，端点距离都会缩小。
// 最大步数：如果能使得每次端点距离只缩小 1 ，那么就是最大的步数；但是因为要向中间移动，第一次端点距离必然剧变，我们取改变后端点距离更大的。
// 最小步数：保持不动的石子尽可能多，也就是长度为 n 的窗口内的石子数越多越好，然后用窗口外的石子去填空。
// 窗内空位数即为所需操作总步数。
// 我们让窗口的左端点对齐有石子的位置（否则窗口左侧空间被浪费），
// 窗口右端点外的石子可以不断填补窗口的右侧空间，直至右端点外只剩一个石子。
// 最坏情况下，此时窗口内的石子都是连续的，那么必须从最左侧拿一个石子放入窗口右端点，然后才能将窗口外的这个石子放入。最少需要 2 步。
// 也即最坏情况为：n - 1 个石子全部连续，此时需要 2 步（空位在窗口端点），或 1 步（如果空位不在端点，这种情况下所需步数等于窗口内的空位数）。
// 虽然我们在操作石子的过程中可以人为避免最坏情况，但是最坏情况如果是初始态，那么就必须被考虑了。
class Solution {
public:
    vector<int> numMovesStonesII(vector<int>& stones) {
        // 先排序
        ranges::sort(stones);
        int n = stones.size();

        // 区间 [s,t] 一共有 t-s+1 个位置，其中 n-1 个原本就有人，
        // 所以还剩下 t-s+1-(n-1) 个空位
        int ma = max(stones[n - 1] - stones[1] + 1, stones[n - 2] - stones[0] + 1) - (n - 1);

        // 不论初始位置怎么样，我们把每个石子一步到位放置，总是能完成游戏，最多移动 n 次
        int mi = n;  // 也可以初始化为 ma ，ma 可能比 n 大得多
        for (int l = 0, r = 0; r < n; ++r) {
            // 窗口内的位置数不得超过 n
            // 也就是说，可以在窗口两边加入石子以补足为长度 n
            while (stones[r] - stones[l] + 1 > n)
                ++l;
            int m = r - l + 1;  // 窗口内的石子个数

            // “n - 1 个石子连续”等价于：
            // (1) 石子个数为 n - 1；
            // (2) 且最大值与最小值的差值等于(石子个数 - 1).
            if (m == n - 1 && stones[r] - stones[l] == r - l)
                mi = min(mi, 2);
            else
                mi = min(mi, n - m);  // n - m 为窗口内的空位数
        }

        return {mi, ma};
    }
};
// @lc code=end
