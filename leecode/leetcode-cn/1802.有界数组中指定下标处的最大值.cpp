/*
 * @lc app=leetcode.cn id=1802 lang=cpp
 *
 * [1802] 有界数组中指定下标处的最大值
 */

// @lc code=start
// 贪心 + 二分查找
// 官方题解：https://leetcode.cn/problems/maximum-value-at-a-given-index-in-a-bounded-array/solutions/2042360/you-jie-shu-zu-zhong-zhi-ding-xia-biao-c-aav4/
// 注意：本题的 n 和 index 都是固定的。
// 因此根据贪心原则，nums[index] 以外的其他数应该尽可能小，也即应该可能快地下降为 1 .
class Solution {
public:
    // index 的位置是固定的
    int maxValue(int n, int index, int maxSum) {
        // 以 index 为界，计算其中一半的元素和
        auto cal = [&](long long hi, int len) -> long long {
            if (hi - len >= 0) {
                return (hi - (len - 1) + hi) * len / 2;
            } else {
                int ones = len - hi;
                return (1 + hi) * hi / 2 + ones;
            }
        };

        auto valid = [&](int hi) {
            // 左半部和右半部： [0,index], [index, n-1]，其中 index 被计入了两次
            return cal(hi, index + 1) + cal(hi, n - index) - hi <= maxSum;
        };

        int left = 1, right = maxSum;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (valid(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }

        return left - 1;
    }
};
// @lc code=end

namespace solution_2 {

// 数学推导
// 官方题解：https://leetcode.cn/problems/maximum-value-at-a-given-index-in-a-bounded-array/solutions/2042360/you-jie-shu-zu-zhong-zhi-ding-xia-biao-c-aav4/
class Solution {
public:
    int maxValue(int n, int index, int maxSum) {
        // TODO
    }
};

}  // namespace solution_2
