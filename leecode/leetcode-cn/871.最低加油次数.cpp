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
// 时间复杂度：O(n^2)
// 空间复杂度：O(n)
namespace solution_2 {
class Solution {
   public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();

        // dp[i] 表示加油 i 次能到达的最远距离
        vector<long long> dp(n + 1);  // 用 long long 防止加法溢出，因为最远距离可能远远大于 target
        dp[0] = startFuel;

        // 依次将 stations[i] 作为最后一次加油的站点，更新 dp[j+1]
        // 这是将空间复杂度优化了的版本
        // 我们也可以直接使用 dp[i][j] 表示将 stations[i] 作为最后一次加油的站点、且总加油了 j 次的最大行驶距离
        for (int i = 0; i < n; ++i) {
            int pos = stations[i][0];
            int fuel = stations[i][1];
            // j 必须从大到小遍历
            // 否则，因为 i 遍历时会用 stations[i] 来更新 dp[j] ，而 dp[j+1] 会用 dp[j] 来更新，
            // 于是 stations[i] 就在 i 遍历时被计入 dp[j+1] 多次了
            // 因为 i 是最后一个加油站点，所以 j 最大为 i
            for (int j = i; j >= 0; --j) {
                if (dp[j] >= pos) {  // 加油 j 次可以到达 stations[i]
                    dp[j + 1] = max(dp[j + 1], dp[j] + fuel);
                }
            }
        }

        for (int i = 0; i <= n; ++i) {
            if (dp[i] >= target)
                return i;
        }

        return -1;
    }
};

}  // namespace solution_2
