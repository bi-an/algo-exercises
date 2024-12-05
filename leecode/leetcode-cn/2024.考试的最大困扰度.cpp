/*
 * @lc app=leetcode.cn id=2024 lang=cpp
 *
 * [2024] 考试的最大困扰度
 */

// @lc code=start
// 滑动窗口
class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int n = answerKey.length(), ans = 0;
        unordered_map<char, int> cnt;
        for (int l = 0, r = 0; r < n; ++r) {
            ++cnt[answerKey[r]];
            // 将 T 或 F 中个数较少的改成另一个即可
            // 判断条件也可写成：
            //  cnt['T'] > k && cnt['F'] > k
            while (min(cnt['T'], cnt['F']) > k) {
                --cnt[answerKey[l++]];
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end
