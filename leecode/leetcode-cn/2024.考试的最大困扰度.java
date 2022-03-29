/*
 * @Author: your name
 * @Date: 2022-03-29 21:14:48
 * @LastEditTime: 2022-03-29 21:16:42
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2024.考试的最大困扰度.java
 */


// 只要求最大连续指定字符的数目时，本题和「1004. 最大连续1的个数 III」完全一致。
// 基本思想：
//  统计 'T' 的最大可能连续个数时，对区间 [left, right] 而言，只要其中的 'F' 的个数不超过 k，
//  那么，可以将这些 'F' 全部反转成 'T'，得到 right - left + 1 个连续的 'T'.
// 滑动窗口：
//  遍历每一个可能的 right，如果 [left, right] 中有超过 k 个 'F'，那么 left++，直至 'F' 个数 <= k。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
    public int maxConsecutiveAnswers(String answerKey, int k) {
        return Math.max(maxConsecutiveChar(answerKey, k, 'T'),
                maxConsecutiveChar(answerKey, k, 'F'));
    }

    public int maxConsecutiveChar(String answerKey, int k, char ch) {
        int ans = 0;
        // sum 记录 [left, right] 区间中另一个字符的个数
        for (int left = 0, right = 0, sum = 0; right < answerKey.length(); ++right) {
            sum += answerKey.charAt(right) != ch ? 1 : 0;
            // 这里换成 if 也可以，因为 sum 是从 0 按步长 1 递增的
            //while (sum > k) {
            if (sum > k) {
                sum -= answerKey.charAt(left++) != ch ? 1 : 0;
            }
            ans = Math.max(ans, right - left + 1);
        }
        return ans;
    }
}
