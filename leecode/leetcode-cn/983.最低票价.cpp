/*
 * @lc app=leetcode.cn id=983 lang=cpp
 *
 * [983] 最低票价
 */

// @lc code=start
// 方法一：记忆化搜索
// 题解：https://leetcode.cn/problems/minimum-cost-for-tickets/solutions/1/jiao-ni-yi-bu-bu-si-kao-dpcong-ji-yi-hua-tkw4
class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        // 从右往左思考，主要是为了方便把递归翻译成递推。从左往右思考也是可以的。
        int last_day = days.back();
        // 哈希表便以快速确认这一天需不需要旅游
        unordered_set<int> day_set(days.begin(), days.end());
        // 记忆化搜索
        // 由于至少会消费一天，所以答案一定不为 0 ，可以用 0 作为初值。
        vector<int> memo(last_day + 1);

        // dfs(i) 表示 1 到 i 天的最小花费。
        // 写法一：
        //  lambda 表达式 dfs 在这里其实是一个变量，定义变量时，不能再引用该变量本身，
        //  否则会陷入无限递归定义。或者说，lambda函数是匿名的，不能在其内部获取到自身的名称。
        //  所以需要将变量 dfs 作为引用（左值引用和右值引用都可以）传入函数参数。
        //  右值引用可以实现完美转发。
        // 写法二：
        //  如果不使用引用，可以将 auto 改成 std::function ，即将其封装为一个函数类型。
        //  即 std::function<int(int)> dfs = [&]( int i) {...}; 也能使得编译通过。
        //  但是 std::function 的开销会大一些。
        // 可以参考：https://blog.csdn.net/wang15188369698/article/details/134836293
        auto dfs = [&](auto&& dfs, int i) {
            if (i <= 0) {
                return 0;
            }
            int& res = memo[i];  // 注意这里是引用
            if (res)
                return res;
            if (!day_set.count(i))
                return res = dfs(dfs, i - 1);
            return res = min({dfs(dfs, i - 1) + costs[0],
                              dfs(dfs, i - 7) + costs[1],
                              dfs(dfs, i - 30) + costs[2]});  // rangs::min
        };

        return dfs(dfs, last_day);
    }
};

// 方法二：动态规划
namespace solution_2 {

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int last_day = days.back();
        unordered_set<int> day_set(days.begin(), days.end());
        vector<int> dp(last_day + 1);

        for (int i = 1; i <= last_day; ++i) {
            if (!day_set.count(i)) {
                dp[i] = dp[i - 1];
                continue;
            }
            // dp[i] = dp[i - 1] + costs[0];
            // if (i >= 7) {
            //     dp[i] = min(dp[i], dp[i - 7] + costs[1]);
            // } else {
            //     dp[i] = min(dp[i], dp[0] + costs[1]); // 这步必不可少
            // }
            // if (i >= 30) {
            //   dp[i] = min(dp[i], dp[i - 30] + costs[2]);
            // } else {
            //     dp[i] = min(dp[i], dp[0] + costs[2]);
            // }

            // 优雅的写法
            dp[i] = min({dp[i - 1] + costs[0],
                         dp[max(i - 7, 0)] + costs[1],
                         dp[max(i - 30, 0)] + costs[2]});
        }

        return dp[last_day];
    }
};

}  // namespace solution_2

// 方法三：三指针优化，降低时空复杂度，动态规划
namespace solution_3 {

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        // dp[i+1] 表示第 days[0] ~ days[i] 天的最少花费
        vector<int> dp(n + 1);
        for (int i = 0, j = 0, k = 0; i < n; ++i) {
            int d = days[i];
            // j, k 是左边界
            while (days[j] <= d - 7) {
                j++;
            }
            while (days[k] <= d - 30) {
                k++;
            }
            dp[i + 1] = min({dp[i] + costs[0],
                             dp[j] + costs[1],
                             dp[k] + costs[2]});
        }
        return dp[n];
    }
};

}  // namespace solution_3

// @lc code=end
