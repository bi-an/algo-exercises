/*
 * @Author: your name
 * @Date: 2022-03-26 17:18:38
 * @LastEditTime: 2022-03-26 17:18:38
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2016.增量元素之间的最大差值.cc
 */

// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int ans = -1, premin = nums[0]; // premin 保存之前的最小值
        for (int num : nums) {
            if (num > premin) {
                ans = max(ans, num - premin);
            } else {
                premin = num;
            }
        }
        return ans;
    }
};