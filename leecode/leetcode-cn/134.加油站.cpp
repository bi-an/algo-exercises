/*
 * @lc app=leetcode.cn id=134 lang=cpp
 *
 * [134] 加油站
 */

// @lc code=start
// 方法一：贪心算法
// 官方题解：https://leetcode.cn/problems/gas-station/solutions/488357/jia-you-zhan-by-leetcode-solution
// 假设从加油站 x 最远只能到达 y ，考虑 [x,y] 中间的某个加油站 z ，
// 因为即使到达 z 时还剩余一些汽油，最远也只能到达 y ，
// 那么如果起始时是从 z 出发（也就是相当于从 x 出发到达 z 时恰好用完所有的汽油）最远也只可能到达 y ，不可能更远到驶完一周。
// 也可以用数学公式来推导以上规律，见官方题解。
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
                ++cnt;  // 只记录符合要求的站点数
            }
            if (cnt == n)
                return i;
            i += cnt + 1;
        }
        return -1;
    }
};

// 方法二：
// 题解：https://leetcode.cn/problems/gas-station/solutions/2933132/yong-zhe-xian-tu-zhi-guan-li-jie-pythonj-qccr
// 该题解一定要查看动图
// 假设剩余油量可以为负数，我们将从站点 0 出发，到达每个站点时的剩余油量画成折线图，并重复一个周期
// 如果单个周期内的折线图的最后一点高于或处于 y 轴（也即是所有站的储油的累加和大于总油耗，此时折线图有断点），那么从油量最低点出发，一定可以走完一个周期。
// 理解：当从其他站点出发时，从哪个加油站出发，就相当于到达该站时恰好用完所有的油，也就是将 y 轴移动到该站点形成的新的折线图，
// 如果从最低点出发，那么整个折线图都将位于 y 轴的上半部分，也就是剩余油量将始终大于等于 0 ，可以到达任意一个站点。
// 我们找出最低的站点，即答案。
namespace solution_2 {
class Solution {
   public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        long long remain = 0, min_remain = LLONG_MAX;
        int ans = -1;
        for (int i = 0; i < gas.size(); ++i) {
            if (remain < min_remain) {
                ans = i;
                min_remain = remain;
            }
            remain += gas[i] - cost[i];
        }
        return remain < 0 ? -1 : ans;
    }
};
}  // namespace solution_2

// @lc code=end
