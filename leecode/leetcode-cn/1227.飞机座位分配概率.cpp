/*
 * @lc app=leetcode.cn id=1227 lang=cpp
 *
 * [1227] 飞机座位分配概率
 */

// @lc code=start
// 概率题。
// 官方题解：https://leetcode.cn/problems/airplane-seat-assignment-probability/solutions/664495/fei-ji-zuo-wei-fen-pei-gai-lu-by-leetcod-gyw4
class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        return n >= 2 ? 0.5 : 1.0;
    }
};
// @lc code=end
