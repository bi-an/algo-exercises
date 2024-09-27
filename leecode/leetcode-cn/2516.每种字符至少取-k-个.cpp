/*
 * @lc app=leetcode.cn id=2516 lang=cpp
 *
 * [2516] 每种字符至少取 K 个
 */

// @lc code=start
// 题解： https://leetcode.cn/problems/take-k-of-each-character-from-left-and-right/solutions/2928177/mei-chong-zi-fu-zhi-shao-qu-k-ge-by-leet-10ct/comments/2391403
class Solution {
public:
    // 处理单个字符的问题，一般有以下解法：
    // (1) 双指针：快慢指针、左右指针
    // (2) 滑动窗口
    // (3) 动态规划，有时候还需要加上哈希表
    //
    // 逆向思维：取走这些字符串后，剩下的字符串是原来的字符的一个子串
    // 我们需要取走最少的字符，就是让剩下的子串长度最大。也就是滑动窗口的最大长度。
    // 其他的字符每种至少取走 k 个，就是窗口内每种字符个数至多为 cnt-k 。
    int takeCharacters(string s, int k) {
        int n = s.length();
        vector<int> cnt(3, -k);  // 初始化为 -k
        // 统计词频
        for (char c : s) {
            ++cnt[c - 'a'];
        }  // 现在 cnt 中保存的是窗口内每种字符的目标计数（最大计数）

        // 如果小于 0 ，说明个数小于 k，不满足题意。
        // 反之，一定能找到答案，最坏情况下把所有的字符都取走
        for (auto cn : cnt) {
            if (cn < 0)
                return -1;
        }

        int l = 0, r = 0, maxL = 0;
        vector<int> rec(3, 0);
        while (l < n - maxL) {  // 剩余窗口大小比 maxL 小，就不需要继续滑动了，因为一定不是最优
            // if (l > r)
            //     r = l; // 这样可能会跳过 rec[r] 的计数，导致出错
            while (r < n && rec[s[r] - 'a'] < cnt[s[r] - 'a']) {
                ++rec[s[r++] - 'a'];  // 注意到，r 总是指向待统计的位置，
                                      // 我们统计完 s[r] 之后，又对 r 进行了自增，
                                      // 即使当 rec 次数与 cnt 相等时， r 也被自增了一次，之后循环结束，
                                      // 所以 r 还是指向的下一个位置，也就是说窗口是左闭右开区间 [l, r)
            }
            maxL = max(maxL, r - l);  // 更新最大长度
            --rec[s[l++] - 'a'];      // 即使上面所有的 r 都不符合条件，也就是没有滑动 r ，
                                      // 此时同样会因为 l 的滑动导致 rec 被更新
                                      // 故 rec 可能为 -1 （当 l 越过 r 时），从而让下一次循环的 r 被滑动
        }
        return n - maxL;
    }
};
// @lc code=end
