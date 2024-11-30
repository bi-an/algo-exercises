/*
 * @lc app=leetcode.cn id=1888 lang=cpp
 *
 * [1888] 使二进制字符串字符交替的最少反转次数
 */

// @lc code=start
// 双倍字符串 + 定长滑动窗口
// 参考题解：https://leetcode.cn/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/
// “类型1”操作的结果，就是将原字符串双倍之后，定长 len 的窗口内的字符串
class Solution {
public:
    int minFlips(string s) {
        int len = s.length();
        string target = "01";

        int cnt = 0;
        // 第一个窗口
        for (int i = 0; i < len; ++i) {
            // 用 "010101..." 数组去对齐 s ，来统计与其不同的字符数
            cnt += (s[i] != target[i % 2]);
        }
        // s 中，与 "101010..." 数组不同的字符数就是 len-cnt ，
        // 因为他们是互补的。
        int ans = min({cnt, len - cnt});
        // 窗口右滑
        // s += s;
        // 不需要真的将 s 扩大两倍，使用下标模拟即可
        for (int i = 0; i < len; ++i) {
            cnt += (s[i] != target[(i + len) % 2]);  // 右端点
            cnt -= (s[i] != target[(i) % 2]);        // 左端点
            ans = min({ans, cnt, len - cnt});
        }
        return ans;
    }
};
// @lc code=end
