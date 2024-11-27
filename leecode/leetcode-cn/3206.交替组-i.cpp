/*
 * @lc app=leetcode.cn id=3206 lang=cpp
 *
 * [3206] 交替组 I
 */

// @lc code=start
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors) {
        int n = colors.size(), ans = 0;
        for (int i = 0; i < n; ++i) {
            int l = (i + n - 1) % n, r = (i + 1) % n;
            if (colors[l] != colors[i] && colors[r] != colors[i])
                ++ans;
        }
        return ans;
    }
};
// @lc code=end
