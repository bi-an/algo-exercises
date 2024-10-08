/*
 * @lc app=leetcode.cn id=1870 lang=cpp
 *
 * [1870] 准时到达的列车最小时速
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
// 二分查找
class Solution {
   public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        // hour 的小数点最多为 2 位，所以为了避开浮点数的精度问题，乘以 100
        // 2.01*100 的结果不是 201，而是 200.9999997 这样的数，所以需要四舍五入
        long long hr = llround(hour * 100);

        // 速度可以无限，但是公交必须整点发车，故每个小时最多乘坐一趟公交。
        // 当且仅当 "hour的整数部分 >= n-1 " 且 "hour的小数部分 > 0 " 时，才不会迟到。
        // 乘以 100 后，小数部分被囊括进入 long long 整型数中，就是
        // hour*100 > (n-1)*100
        // 反之则迟到，即
        if ((n - 1) * 100 >= hr)
            return -1;

        // 对速度进行二分查找，寻找左边界
        // 速度是正整数，所以最小值为 1 ；
        // 速度的最大值不会超过 dist[i] / 0.01 ，其中， 0.01 是 hour 的最小值（因为精度为 0.01 ）。
        int l = 1, r = 1e7;  // dist[i] ≤ 1e5
        while (l < r) {
            int mid = l + (r - l) / 2;  // (l+r) 可能越界
            // 前 n-1 趟公交，所用时间要向上取整，因为公交是整点出发；
            // 第 n 趟公交，所用时间需要向下取整，因为总时间需要小于等于 hour ；
            long long t = 0;
            for (int i = 0; i < n - 1; ++i) {
                t += (dist[i] - 1) / mid + 1;  // 向上取整
            }
            // t + dist[n-1]/mid ≤ hour
            // 上式两边乘以 100 ，得 100*(t + dist[n-1]/mid) ≤ hr
            // 注意：除法可能丢失精度，使得左式总是 100 的倍数，导致结果有偏差
            // 故写成 100*(mid*t + dist[n-1]) ≤ hr*mid
            // if (100 * (t + dist[n - 1] / mid) <= hr) { // 错误写法！不精确！
            t *= mid;
            t += dist[n - 1];
            if (t * 100 <= hr * mid) {
                r = mid;  // 保留可能的左边界
            } else {
                l = mid + 1;  // mid 不符合条件
            }
            // cout << l << "," << r << endl;
        }

        return l;
    }
};
// @lc code=end

void test1() {
    Solution sol;
    vector<int> dist = {1, 3, 2};
    double hour = 6;
    int ans = sol.minSpeedOnTime(dist, hour);
    cout << ans << endl;
}

void test2() {
    Solution sol;
    vector<int> dist = {1, 3, 2};
    double hour = 2.7;
    int ans = sol.minSpeedOnTime(dist, hour);
    cout << ans << endl;
}

void test3() {
    Solution sol;
    vector<int> dist = {1, 1, 100000};
    double hour = 2.01;
    int ans = sol.minSpeedOnTime(dist, hour);
    cout << ans << endl;
}

void test4() {
    Solution sol;
    vector<int> dist = {1, 1};
    double hour = 1.0;
    int ans = sol.minSpeedOnTime(dist, hour);
    cout << ans << endl;
}

int main() {
    test3();

    return 0;
}