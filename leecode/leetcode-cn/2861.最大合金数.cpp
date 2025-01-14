/*
 * @lc app=leetcode.cn id=2861 lang=cpp
 *
 * [2861] 最大合金数
 */

// 二分查找
class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        auto check = [&](int m) {
            for (auto& elements : composition) {
                long long money = budget;
                for (int i = 0; i < elements.size(); ++i) {
                    long long quantity = (long long)elements[i] * m - stock[i];
                    if (quantity > 0)
                        money -= cost[i] * quantity;
                }
                if (money >= 0)
                    return true;
            }
            return false;
        };

        // 题解：https://leetcode.cn/problems/maximum-number-of-alloys/solutions/2446024/er-fen-da-an-fu-ti-dan-by-endlesscheng-3jdr/

        // 可以将 right 设置为 min(stock)+budget
        // 因为根据木桶原理，将 budget 全部用来补足最短板：
        // （1）如果补足之后，其还是最短板，那么上界还是其本身；
        // （2）如果补足之后，其不是最短板，那么其是不可能达到的上界。

        // int right = 200'000'000;  // budget, stock[i] ≤ 10⁸
        // int left = 0, right = ranges::max(stock) + budget;

        int left = 0, right = ranges::min(stock) + budget;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left - 1 >= 0 ? left - 1 : 0;
    }
};

namespace version_2 {

// @lc code=start
// 题解：https://leetcode.cn/problems/maximum-number-of-alloys/solutions/2446024/er-fen-da-an-fu-ti-dan-by-endlesscheng-3jdr/
// 也可以对每个 composition[i] 进行二分查找，
// 此时下一个 composition[i] 的 left 可以实时更新为 ans ，因为其是最新的下界。
class Solution {
public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        int ans = 0;

        for (auto& comp : composition) {
            auto check = [&](int num) {
                long long money = budget;
                for (int i = 0; i < comp.size(); ++i) {
                    long long need = (long long)num * comp[i] - stock[i];
                    if (need > 0) {
                        money -= need * cost[i];
                        if (money < 0)
                            return false;
                    }
                }

                return true;
            };

            // left 每次更新为 ans
            int left = ans, right = ranges::max(stock) + budget;
            while (left <= right) {
                int mid = (left + right) / 2;
                if (check(mid))
                    left = mid + 1;
                else
                    right = mid - 1;
            }

            ans = left - 1 >= ans ? left - 1 : ans;
        }

        return ans;
    }
};
// @lc code=end

}  // namespace version_2
