/*
 * @lc app=leetcode.cn id=825 lang=cpp
 *
 * [825] 适龄的朋友
 */

// @lc code=start
// 双指针 + 滑动窗口
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int n = ages.size();
        sort(ages.begin(), ages.end());
        // 合法范围 ages[x]*0.5+7 < ages[y] ≤ ages[x]
        // 考虑到 age 可能相同，相互之间会互相加好友，所以需要对每一个 age ，求其窗口；
        // 由于窗口边界只增不减，所以窗口不会被重复计算，时间复杂度没有因此上升。
        int left = 0, right = 0, ans = 0;
        for (int age : ages) {
            while (left < n && ages[left] <= age * 0.5 + 7)
                ++left;
            while (right < n && ages[right] <= age)
                ++right;
            // 左闭右开区间
            // 注意到，age 本身在该范围内，应该排除
            // cout << left << " " << right << endl;
            // left 可能大于 right
            if (left < right)
                ans += right - left - 1;
        }
        return ans;
    }
};

// 方法二：用计数代替排序 + 前缀和
// 由于 age 的范围为 [1, 120] ，我们只关心符合条件的年龄的数目，所以可以用计数代替排序；
// 对于计数的数列，我们可以使用前缀和快速累计符合条件的年龄的数目的范围和。
// TODO
// @lc code=end
