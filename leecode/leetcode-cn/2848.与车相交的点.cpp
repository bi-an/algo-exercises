/*
 * @lc app=leetcode.cn id=2848 lang=cpp
 *
 * [2848] 与车相交的点
 */

// @lc code=start
// 合并线段
// 时间复杂度：O(nlogn)
// 空间复杂度：O(logn)
class Solution {
public:
    int numberOfPoints(vector<vector<int>>& nums) {
        // 排序：时间O(nlogn)，空间(logn)
        sort(nums.begin(), nums.end(), [](vector<int>& seq1, vector<int>& seq2) {
            if (seq1[0] != seq2[0])
                return seq1[0] < seq2[0];
            return seq1[1] - seq1[0] < seq2[1] - seq2[0];
        });

        int ans = 0;
        int s1 = 0, e1 = -1; // start, end
        for (vector<int>& seq : nums) {
            int s2 = seq[0], e2 = seq[1];
            if (s2 > e1) {
                ans += e1 - s1 + 1;
                s1 = s2;
                e1 = max(e1, e2); // 可能出现s2>s1、e2<e1的情况
            } else {
                e1 = max(e1, e2);
            }
        }
        ans += e1 - s1 + 1;
        return ans;
    }
};

// 官方题解有直接模拟的方法复杂度为O(nC)，然后用差分数组将时间复杂度优化为O(n+C)，
// 其中C是nums[i]的数值范围。
// 这种方法不是最优，不推荐。
// @lc code=end
