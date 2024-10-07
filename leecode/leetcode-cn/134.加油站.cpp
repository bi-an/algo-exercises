/*
 * @lc app=leetcode.cn id=134 lang=cpp
 *
 * [134] 加油站
 */

// @lc code=start
// 贪心算法
// 官方题解：https://leetcode.cn/problems/gas-station/solutions/488357/jia-you-zhan-by-leetcode-solution
// 假设从加油站 x 最远只能到达 y ，考虑 [x,y] 中间的某个加油站 z ，
// 因为即使到达 z 时还剩余一些汽油，最远也只能到达 y ，
// 那么如果起始时是从 z 出发（也就是相当于从 x 出发到达 z 时恰好用完所有的汽油）最远也只可能到达 y ，不可能更远到驶完一周。
// 发现了这个规律，我们下一次只需要从 y+1 开始搜寻。
class Solution {
   public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();

        int i = 0;
        while (i < n) {
            long long sumOfGas = 0, sumOfCost = 0;
            int cnt = 0;
            while (cnt < n) {
                int j = (i + cnt) % n;
                sumOfGas += gas[j];
                sumOfCost += cost[j];
                if (sumOfCost > sumOfGas)
                    break;
                ++cnt;  // 此时已经判断过 sumOfCost > sumOfGas
            }
            if (cnt == n)
                return i;
            i += cnt + 1;
        }
        return -1;
    }
};
// @lc code=end
