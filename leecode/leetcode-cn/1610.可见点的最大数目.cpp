/*
 * @lc app=leetcode.cn id=1610 lang=cpp
 *
 * [1610] 可见点的最大数目
 */

// @lc code=start
// 1. 全部化成极坐标
// 2. atan2(y, x) 求 y/x 的反正切，值域为 [-π, π]
// 3. 需要环形遍历：例如：{0->1, 1->2} 没有遍历完，还需要遍历 {2->0} 。
//    可以增加一个周期，以避免边界讨论。
// 方法一：滑动窗口
class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<double> radians;
        // 如果点处于极坐标原点，需要单独处理（此时 atan2 的返回值也可能不确定）。
        int ans = 0, same = 0;
        for (auto& p : points) {
            int px = p[0] - location[0], py = p[1] - location[1];
            if (px == 0 && py == 0)
                ++same;
            else
                radians.push_back(atan2(py, px));
        }
        ranges::sort(radians);
        // 增加一个周期
        int m = radians.size();
        for (int i = 0; i < m; ++i) {
            radians.push_back(radians[i] + M_PI * 2);
        }
        double radian = angle * M_PI / 180;
        // 滑动窗口
        // 遍历每个左端点，右端点尽可能伸展，这样才能走完一个完整环
        for (int l = 0, r = 0; l < m; ++l) {
            while (r < radians.size() && radians[l] + radian >= radians[r])
                ++r;
            ans = max(ans, r - l);
        }
        return ans + same;
    }
};
// @lc code=end

// 方法二：二分查找，与滑动窗口本质相同，每次二分查找右边界 d + angle
namespace solution_2 {

class Solution {
public:
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        vector<double> radians;
        // 如果点处于极坐标原点，需要单独处理（此时 atan2 的返回值也可能不确定）。
        int ans = 0, same = 0;
        for (auto& p : points) {
            int px = p[0] - location[0], py = p[1] - location[1];
            if (px == 0 && py == 0)
                ++same;
            else
                radians.push_back(atan2(py, px));
        }
        ranges::sort(radians);
        // 增加一个周期
        int m = radians.size();
        for (int i = 0; i < m; ++i) {
            radians.push_back(radians[i] + M_PI * 2);
        }
        double radian = angle * M_PI / 180;
        // 遍历左端点，二分查找右端点
        for (int l = 0; l < m; ++l) {
            auto it = upper_bound(radians.begin(), radians.end(), radians[l] + radian);
            int r = it - radians.begin();
            ans = max(ans, r - l);
        }
        return ans + same;
    }
};

}  // namespace solution_2
