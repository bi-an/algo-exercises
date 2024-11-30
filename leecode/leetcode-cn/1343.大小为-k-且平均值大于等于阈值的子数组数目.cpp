/*
 * @lc app=leetcode.cn id=1343 lang=cpp
 *
 * [1343] 大小为 K 且平均值大于等于阈值的子数组数目
 */

// @lc code=start
// 定长滑动窗口
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        long long tar = (long long)k * threshold, sum = 0;
        int cnt = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum += arr[i];
            if (i < k - 1)
                continue;
            if (sum >= tar)
                ++cnt;
            // 删掉窗口头部元素，为下次作准备
            sum -= arr[i - k + 1];
        }
        return cnt;
    }
};
// @lc code=end
