/*
 * @lc app=leetcode.cn id=904 lang=cpp
 *
 * [904] 水果成篮
 */

// @lc code=start
class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size(), ans = 0;
        unordered_map<int, int> visit;
        for (int l = 0, r = 0; r < n; ++r) {
            ++visit[fruits[r]];
            while (visit.size() > 2) {
                int k = fruits[l++];
                if (--visit[k] == 0)
                    visit.erase(k);
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
// @lc code=end
