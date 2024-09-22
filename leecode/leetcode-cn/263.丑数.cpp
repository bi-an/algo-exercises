/*
 * @lc app=leetcode.cn id=263 lang=cpp
 *
 * [263] 丑数
 */

// @lc code=start
class Solution {
public:
    bool isUgly(int n) {
        if (n <= 0)
            return false;
        vector<int> factors = {2, 3, 5};
        for (auto f : factors) {
            while (n % f == 0) {
                n /= f;
            }
        }
        return n == 1;
    }
};
// @lc code=end
