/*
 * @lc app=leetcode.cn id=2306 lang=cpp
 *
 * [2306] 公司命名
 */

// @lc code=start
// 参考官方题解：https://leetcode.cn/problems/naming-a-company/solutions/2924661/gong-si-ming-ming-by-leetcode-solution-v1s3/
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        unordered_map<char, unordered_set<string>> names;
        for (auto& s : ideas) {
            names[s[0]].insert(s.substr(1));
        }

        // 算交集的时间：O(n)
        auto get_intersection_size = [](const auto& a, const auto& b) {
            int ans = 0;
            for (auto& s : a) {
                // 这里有两条语句 if 和 ++ ，所以效率比直接 ans += b.count(s) 低
                // if (b.count(s)) {
                //     ++ans;
                // }
                ans += b.count(s);  // 使用 unordered_set 的目的是使得求交集时
                                    // 能在 O(1) 时间找到 b 中的元素
            }
            return ans;
        };

        long long ans = 0;
        // 遍历所有前缀的组合，求其后缀集合的差集的元素个数
        for (char i = 'a'; i <= 'z'; ++i) {
            for (char j = 'a'; j < i; ++j) {
                // for (char j = 'a'; j <= 'z'; ++j) {
                // if (i == j) // 如果前缀相等，那么交换之后的结果等于这两个字符串本身，必然不符合。
                //             // 这种写法，ans 不需要乘以 2
                //     continue;
                int m = get_intersection_size(names[i], names[j]);
                ans += (long long)(names[i].size() - m) * (names[j].size() - m);
            }
        }

        return ans * 2;
    }
};

namespace solution_2 {
// 方法一中算交集可以使用动态规划在 O(|Σ|^2) 时间内先计算出来
// 时间复杂度可以变得更低
// 参考题解：https://leetcode.cn/problems/naming-a-company/solutions/1596320/by-endlesscheng-ruz8/
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        // TODO
    }
};

}  // namespace solution_2

// @lc code=end
