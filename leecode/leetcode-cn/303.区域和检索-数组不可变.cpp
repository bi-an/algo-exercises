/*
 * @lc app=leetcode.cn id=303 lang=cpp
 *
 * [303] 区域和检索 - 数组不可变
 */

// @lc code=start
// sumRange()时间复杂度O(1), 空间复杂度O(n)
class NumArray {
public:
    NumArray(vector<int> &nums) {
        dp.resize(nums.size() + 1);
        dp[0] = 0;
        for (int i = 1; i < dp.size(); i++) {
            dp[i] = dp[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int i, int j) {
        return dp[j + 1] - dp[i];
    }

private:
    std::vector<int> dp;
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */
// @lc code=end
