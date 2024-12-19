/*
 * @lc app=leetcode.cn id=1574 lang=cpp
 *
 * [1574] 删除最短的子数组使剩余数组有序
 */

// @lc code=start
// 官方题解：https://leetcode.cn/problems/shortest-subarray-to-be-removed-to-make-array-sorted/solutions/2188366/shan-chu-zui-duan-de-zi-shu-zu-shi-sheng-do2f/
// 题解中倒数第二段“直到前面的元素小于当前所指元素”描述错误，正确做法参见代码。
class Solution {
public:
    int findLengthOfShortestSubarray(vector<int>& arr) {
        int n = arr.size(), j = n - 1;
        // j 先到达右边上升区间的底部，即此时留下的区间为 [j, n-1]
        // 换言之，我们的滑动窗口是待删除的区间，即为 [0, j-1]
        while (j > 0 && arr[j - 1] <= arr[j])
            j--;
        if (j == 0)
            return 0;
        // 然后对每个 i ，让 j 后退，记录最优值
        int res = j;  // 截至此时的最优答案
        for (int i = 0; i < j; ++i) {
            // i 被移出窗口
            // 先将 j 退至合法值
            while (j < n && arr[j] < arr[i])
                j++;
            // i 在窗口外 ，即 [i+1, j-1] ，或者说 (i, j) ，或者说 [i+1, j)
            res = min(res, j - i - 1);
            if (i + 1 < n && arr[i + 1] < arr[i])
                break;
        }
        return res;
    }
};
// @lc code=end
