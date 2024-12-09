/*
 * @lc app=leetcode.cn id=2106 lang=cpp
 *
 * [2106] 摘水果
 */

// @lc code=start
// 题解作者：bi-an
// https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/3015664/hua-dong-chuang-kou-fa-xian-gui-lu-by-bi-o3h6
//
// 不定长滑动窗口
// (1) 如果窗口内所有水果都位于人的同一侧，那么沿着一个方向走即可。
// (2) 如果窗口内的水果在人的两侧都有，要想拿走窗口 [posLeft, posRight] 内的所有水果，那么最少步数耗费的方案为：先走到离自己最近的窗口边界，然后折返到另一个边界。
// 发现规律：这两种情况，步数耗费都可以拆分为两部分：
// 步数耗费 = 窗口长度 + 人与最近窗口边界的距离
// 即 cost = (postRight - postLeft) + min{ |startPos - posLeft|, |startPos - posRight|}
// 这样就不需要区别以上两种情况了。
//
// 如果有些题目不能发现规律，那么也可以把两种走法都试一遍：
// (1) 总是先往左再往右；
// (2) 总是先往右再往左；
// 然后选出两者较优的解。
// 参见：https://leetcode.cn/problems/maximum-fruits-harvested-after-at-most-k-steps/solutions/2254860/hua-dong-chuang-kou-jian-ji-xie-fa-pytho-1c2d/
class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        // 水果总数不会超过 amount[i] * fruits.length = 10⁴ * 10⁵ = 10⁹ ，处于 int 的表示范围内（2³¹
        int n = fruits.size(), cnt = 0, ans = 0;
        // 遍历窗口右端点
        for (int left = 0, right = 0; right < fruits.size(); ++right) {
            int posRight = fruits[right][0];
            // 我们是从左往右遍历，如果右端点在人的右侧，且距离大于 k ，那么从此以后都不会符合约束条件
            if (posRight - startPos > k)
                break;
            cnt += fruits[right][1];
            // 不断右移窗口左端点，直至窗口合法
            // 这个 if 条件是为了优化时间复杂度：如果窗口左端点处于人的右侧或恰好位于人所在位置，右移左端点不能减少步数，可以直接跳过
            if (fruits[left][0] < startPos) {
                while (left <= right && (posRight - fruits[left][0]) + min(abs(posRight - startPos), abs(fruits[left][0] - startPos)) > k) {
                    cnt -= fruits[left][0] < startPos ? fruits[left][1] : 0;
                    ++left;
                }
            }
            // 记录本次局部最优解
            ans = max(ans, cnt);
        }
        return ans;
    }
};
// @lc code=end
