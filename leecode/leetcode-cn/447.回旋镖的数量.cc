/*
 * @Author: your name
 * @Date: 2021-09-13 23:24:04
 * @LastEditTime: 2021-09-13 23:24:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\447.回旋镖的数量.cc
 */

// https://leetcode-cn.com/problems/number-of-boomerangs/
// 时间复杂度O(n^2)
// 空间复杂度O(n)
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& points) {
        int ans = 0;
        // 把回旋镖看作一个V字
        for(vector<int>& c : points) { // V字中心点
            unordered_map<int, int> cnt;
            for(vector<int>& o : points) { // V字两边的点
                int dis = pow(o[0] - c[0], 2) + pow(o[1] - c[1], 2);
                cnt[dis]++;
            }
            for(auto& [_, m] : cnt) {
                ans += m * (m-1); // 排列数A(m,2)
            }
        }

        return ans;
    }
};