/*
 * @lc app=leetcode.cn id=2332 lang=cpp
 *
 * [2332] 坐上公交的最晚时间
 */

// @lc code=start
// 模拟法
// @author bi-an
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());

        int n = buses.size(), m = passengers.size();
        int i = 0;
        int last = -1;
        int ans = -1;
        for (int t : buses) {
            int cnt = 0;
            while (cnt < capacity && i < m && passengers[i] <= t) {
                last = i;
                ++cnt;
                ++i;
            }
            if (t == buses[n - 1] && cnt < capacity && (last == -1 /* cnt == 0*/ || passengers[last] < t))
                return t;
        }

        for (int j = last; j >= 0; --j) {
            ans = passengers[j] - 1;
            if (j - 1 >= 0 && ans > passengers[j - 1])
                break;
        }

        return ans;
    }
};

// 写法二
namespace solution_2 {
// 官方题解
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());

        int space, i = 0;  // i 始终指向下一个等待上车的人
        for (int arrive : buses) {
            space = capacity;  // 能反映最后一趟公交剩余座位数
            while (space > 0 && i < passengers.size() && passengers[i] <= arrive) {
                --space;
                ++i;
            }
        }
        --i;                                                           // 最后一个已上车的人
        int lastCatchTime = space > 0 ? buses.back() : passengers[i];  // 当前可能的最大值
        while (i >= 0 && passengers[i] == lastCatchTime) {
            --i;
            --lastCatchTime;
        }
        return lastCatchTime;
    }
};

}  // namespace solution_2

// @lc code=end
