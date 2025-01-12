/*
 * @lc app=leetcode.cn id=1642 lang=cpp
 *
 * [1642] 可以到达的最远建筑
 */

// @lc code=start
// 反悔贪心 + 堆
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int i = 1, n = heights.size();
        priority_queue<int> pq;  // 最大堆
        for (; i < n; ++i) {
            int delta = heights[i] - heights[i - 1];
            if (delta <= 0)
                continue;

            /** START 写法一 */
            // // 梯子相当于无限高度的砖块
            // // 万不得已才使用梯子，使用时调整局部最优值，将梯子用在当前最大高度差的位置
            // if (bricks < delta && ladders > 0 && !pq.empty() && pq.top() > delta) {
            //     bricks += pq.top();
            //     pq.pop();
            //     --ladders;
            // }

            // // 先用砖块
            // if (bricks >= delta) {
            //     pq.push(delta);
            //     bricks -= delta;
            // } else if (ladders > 0) {
            //     --ladders;
            // } else {
            //     break;
            // }
            /** END 写法一 */

            /** START 写法二 */
            pq.push(delta);
            bricks -= delta;  // 当前使用砖块
            // 如果 bricks 不足，那么一直选之前最大高度差处，换梯子
            while (bricks < 0 && ladders > 0 && !pq.empty()) {
                bricks += pq.top();
                pq.pop();
                --ladders;
            }
            // 所有梯子和砖块都耗尽
            if (bricks < 0)
                break;
            /** END 写法二 */
        }

        return i - 1;
    }
};
// @lc code=end

namespace version_2 {

// 题解：https://leetcode.cn/problems/furthest-building-you-can-reach/solutions/468787/ke-yi-dao-da-de-zui-yuan-jian-zhu-by-zerotrac2/
// 同方法一：贪心 + 反悔 + 堆
// 先使用梯子也可以，当梯子用尽，则调整局部最优，将最小的高度差改成用砖块
// 此时应该使用堆来维护使用梯子处的高度差
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int i = 1, n = heights.size();
        priority_queue<int, vector<int>, greater<>> pq;  // 使用梯子处的高度差
        for (; i < n; ++i) {
            int delta = heights[i] - heights[i - 1];
            if (delta > 0) {
                pq.push(delta);  // 注意：我们将当前的高度先统计进入了，其可能被反悔掉
                if (pq.size() > ladders) {
                    bricks -= pq.top();  // 将其中最小高度差处改用砖块
                    pq.pop();
                }
                // 砖块小于 0 ，一定是因为梯子用尽、改用砖块时造成的
                if (bricks < 0)
                    break;
            }
        }
        return i - 1;
    }
};

}  // namespace version_2

namespace solution_2 {

// 方法二：二分查找
class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        // TODO
    }
};

}  // namespace solution_2
