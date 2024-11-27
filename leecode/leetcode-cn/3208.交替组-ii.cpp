/*
 * @lc app=leetcode.cn id=3208 lang=cpp
 *
 * [3208] 交替组 II
 */

#include <bits/stdc++.h>
using namespace std;

// 写法一：
// 用一个 record 数组记录当前项与后项是否颜色相同，相同则记作 1 ，不同则记作 0；
// 定义 sum[i] 为长度为 k 的组 { record[i-k+1], ..., record[i] } 的和。
// 那么，如果 sum[i] 等于 k - 1 ，则该组满足题意。
// 时间复杂度：O(n)
// 空间复杂度：O(n)
namespace solution_1 {

class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size(), cnt = 0;
        vector<int> rec(n);  // 与后项是否颜色相同
        for (int i = 0; i < n; ++i) {
            rec[i] = (colors[i] != colors[(i + 1) % n]);
        }
        vector<int> sum(n);  // 以 rec[i] 结尾的长度为 k 的组和
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                for (int j = i - k + 1 + n; j < n; ++j) {
                    sum[i] += rec[j];
                }
                cout << endl;
            } else {
                sum[i] = sum[i - 1] + rec[i - 1] - rec[(i - k + n) % n];
            }
            if (sum[i] == k - 1)
                ++cnt;
        }
        return cnt;
    }
};

}  // namespace solution_1

// 写法二：
// 在写法一中，我们引入 record 数组是为了方便统计不同颜色块的个数；
// 引入 sum 数组也是为了查询 sum[i] 。实际上用一个数 cnt 来统计即可。
// 时间复杂度：O(n)
// 空间复杂度：O(1)
namespace solution_2 {

class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size(), cnt = 0, ans = 0;
        // 判断与前项是否相同
        // cnt 表示以 colors[i] 结尾的组的不同颜色块的个数
        for (int i = -k + 2; i < n; ++i) {
            if (colors[(i + n) % n] != colors[(i - 1 + n) % n])
                cnt++;
            if (i > 0 && colors[(i - k + 1 + n) % n] != colors[(i - k + n) % n])
                --cnt;
            if (cnt == k - 1)
                ++ans;
        }
        return ans;
    }
};

}  // namespace solution_2

// @lc code=start
// 写法三：
// 因为我们需要 k 个块的颜色交替，如果当前块与前项颜色相同，那么包含这两个块的长度为 k 的组必然不符合要求，需要剔除；
// 也就是，新的满足条件的组必然不能包括前项，必须从当前项重新开始（以当前项为首项）。
// 所以，我们可以将 cnt 改为统计以当前颜色块结尾的、当前遇到的、最长颜色交替的颜色块的个数，
// 于是，cnt 需要初始为 1 ； cnt >= k 表示交替组的长度大于等于 k ，则长度为 k 的子交替组也满足题意。
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int n = colors.size(), cnt = 1, ans = 0;
        // 判断与前项是否相同
        for (int i = -k + 2; i < n; ++i) {
            if (colors[(i + n) % n] != colors[(i - 1 + n) % n])
                cnt++;
            else
                cnt = 1;
            if (cnt >= k)
                ++ans;
        }
        return ans;
    }
};
// @lc code=end

void testCore(vector<int> colors, int k) {
    Solution sol;
    int ans = sol.numberOfAlternatingGroups(colors, k);
    cout << __func__ << ": " << ans << endl;
}

int main() {
    testCore({0, 1, 0, 1, 0}, 3);
    testCore({0, 1, 0, 0, 1, 0, 1}, 6);
    testCore({1, 1, 0, 1}, 4);

    return 0;
}
