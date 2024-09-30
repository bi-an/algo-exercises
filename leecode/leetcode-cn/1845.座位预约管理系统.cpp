/*
 * @lc app=leetcode.cn id=1845 lang=cpp
 *
 * [1845] 座位预约管理系统
 */

// @lc code=start
// 动态维护最小值，那么二叉堆是一个方案。
// 方案一：将所有的可预约的座位存入二叉堆，空间复杂度为 O(n) ，时间复杂度为 O(logn) ；
// 方案二：本题隐含一个条件：每次 reserve 都是选择当前最小的座位编号；
//        假设没有 unreserve 过，那么 reserve 时直接将已经预约过的座位号加 1 即可；
//        如果发生过 unreserve ，我们把所有的 unreserve 的座位都存入二叉堆，
//        那么以后 reserve 时，二叉堆中的最小值，就是当前可预约的最小值。
//        空间复杂度等于 unreserve 的次数 N，空间复杂度也随着二叉堆的空间复杂度的降低
//        而降为 O(logN) 。
class SeatManager {
    int seat = 0;                                    // 已经预定过的座位数（也是座位编号，因为编号从 1 开始）
    priority_queue<int, vector<int>, greater<>> mn;  // unreserve 的最小值
public:
    SeatManager(int n) {
    }

    int reserve() {
        int res = -1;
        if (!mn.empty()) {
            res = mn.top();
            mn.pop();
        } else {
            res = ++seat;
        }
        return res;
    }

    void unreserve(int seatNumber) {
        // 没有判断 seatNumber 是否合规
        mn.push(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
// @lc code=end
