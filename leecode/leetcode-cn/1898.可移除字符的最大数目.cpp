/*
 * @lc app=leetcode.cn id=1898 lang=cpp
 *
 * [1898] 可移除字符的最大数目
 */

// @lc code=start
class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        int n = s.length(), m = p.length();

        // vector<bool> 是用位图表示的，所以不支持按引用操作，
        // 这使其不适配很多 STL 算法的接口，例如 ranges::fill
        vector<bool> del(n);
        auto check = [&](int k) {
            fill(del.begin(), del.end(), false);
            for (int i = 0; i < k; ++i)
                del[removable[i]] = true;  // 表示这个位置在 s 中被删除了

            for (int i = 0, j = 0; i < n; ++i) {
                if (!del[i] && s[i] == p[j] && ++j == m)
                    return true;
            }

            return false;
        };

        int left = 0, right = removable.size() + 1;
        while (left + 1 < right) {
            int mid = (left + right) / 2;
            (check(mid) ? left : right) = mid;
        }

        return left;
    }
};
// @lc code=end
