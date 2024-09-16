/*
 * @lc app=leetcode.cn id=1184 lang=cpp
 *
 * [1184] 公交站间的距离
 */

// @lc code=start
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int n = distance.size();
        vector<int> pre(n + 1);
        for (int i = 0; i < n; ++i) {
            pre[i + 1] = pre[i] + distance[i];
            cout << pre[i + 1] << ",";
        }
        if (destination < start)
            swap(start, destination);
        int dist1 = pre[destination] - pre[start];
        int dist2 = pre[n] - dist1;
        return min(dist1, dist2);
    }
};
// @lc code=end
