/*
 * @lc app=leetcode.cn id=871 lang=cpp
 *
 * [871] 最低加油次数
 */

// @lc code=start
// 方法一：反悔贪心
// 题解：https://leetcode.cn/problems/minimum-number-of-refueling-stops/solutions/2921064/zui-da-dui-tan-xin-pythonjavacgojsrust-b-yldp
// 时间复杂度：O(nlogn)，最大堆的时间复杂度为 logn
// 空间复杂度：O(n)
class Solution {
   public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int, vector<int>> mx;  // 最大堆
        int cnt = 0, curPos = startFuel;      // 当前的油量能到达的最远距离

        for (auto& s : stations) {
            int pos = s[0], fuel = s[1];
            // 这一步可以去掉，因为题设已知 pos < target
            if (pos > target)
                break;
            while (!mx.empty() && curPos < pos) {
                // 反悔，选一个油量最多的加油站加油
                curPos += mx.top();
                mx.pop();
                ++cnt;
            }
            if (curPos < pos)
                return -1;
            mx.push(fuel);
        }

        while (curPos < target && !mx.empty()) {
            curPos += mx.top();
            mx.pop();
            ++cnt;
        }

        return curPos < target ? -1 : cnt;
    }
};
// @lc code=end

// 方法二：动态规划
