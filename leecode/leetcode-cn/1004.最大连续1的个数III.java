/*
 * @Author: your name
 * @Date: 2022-03-29 21:15:27
 * @LastEditTime: 2022-03-29 21:15:27
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\1004.最大连续1的个数III.java
 */


// 本题和「2024. 考试的最大困扰度」完全一致。
// @ref 官方题解
// 滑动窗口
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
    public int longestOnes(int[] nums, int k) {
        int ans = 0;
        for (int left = 0, right = 0, sum = 0; right < nums.length; ++right) {
            sum += nums[right] == 0 ? 1 : 0;
            if (sum > k) {
                sum -= nums[left++] == 0 ? 1 : 0;
            }
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }
}
