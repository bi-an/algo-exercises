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

            // 左闭右开区间 [l, r) ，r 指向下一个待统计的位置，
            // 如果计数少于目标计数，就加入到滑动窗口中（ r 向右滑动），
            // 直到等于目标计数为止
            while (r < n && rec[s[r] - 'a'] < cnt[s[r] - 'a']) {
                ++rec[s[r++] - 'a'];
            }
            maxL = max(maxL, r - l);  // 更新最大长度
            // 注意到，如果当前窗口中的计数为 0 ，那么当 l 右滑的时候，
            // 可能超过 r ，但是不需要担心，因为此时，其计数会自减为 -1 ，
            // 这会使得下一次 r 再次右滑动，将计数自增为 0 。
            --rec[s[l++] - 'a'];
        }
        return n - maxL;
    }
};
// @lc code=end

// 二刷，解法相同
// 2024-12-07 18:58:49
namespace solution_2 {
class Solution {
public:
    int takeCharacters(string s, int k) {
        int ans = 0, n = s.length();
        // 反向思考：从两边取，剩余的就是一个滑动窗口。
        // 约束条件：
        // 每种至少取走 k 个，也就是最多剩余 m - k 个，m 是原来的计数
        // 也即是窗口内每种最多剩余 m - k 个。
        // 解：
        // 返回所需的最少分钟数，也即我们需要找到最大窗口

        // cnt1 原数组的计数
        // cnt2 窗口内的计数
        unordered_map<char, int> cnt1, cnt2;
        for (char a : s)
            ++cnt1[a];

        for (char c : {'a', 'b', 'c'}) {
            if (cnt1[c] < k)
                return -1;
        }

        for (int l = 0, r = 0; l < n && r < n; ++r) {
            ++cnt2[s[r]];
            // 之前的窗口是合法的，加入 s[r] 才不合法了
            // cnt1[x] - k 可能小于 0
            while (l < n && cnt2[s[r]] > cnt1[s[r]] - k)
                --cnt2[s[l++]];
            // 如果都不合法，right 会大于 left
            ans = max(ans, r - l + 1);
        }

        return n - ans;
    }
};
}  // namespace solution_2
