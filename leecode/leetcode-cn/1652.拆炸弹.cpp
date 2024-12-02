/*
 * @lc app=leetcode.cn id=1652 lang=cpp
 *
 * [1652] 拆炸弹
 */

// @lc code=start
// 定长滑动窗口
// 循环数组，引入双倍原数组思考，然后滑动窗口
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int n = code.size();
        vector<int> ans(n);
        // 滑动窗口
        // k >= 0 ，则第一个窗口为 [1, k+1) ；
        // k < 0 ，则第一个窗口为 [n-|k|, n) 。
        int r = k > 0 ? k + 1 : n;  // 右端点（不含）
                                    // 如果考虑左端点，则需要考虑 k 的符号，比较麻烦
        k = abs(k);
        // 计算第一个窗口
        // reduce() 和 accumulate() 功能相同，但是是使用 map-reduce 并行计算的，reduce 翻译为“归约”。
        long long sum = reduce(code.begin() + r - k, code.begin() + r);
        for (int i = 0; i < n; ++i) {
            ans[i] = sum;
            // 加入右端点
            sum += code[(r + i) % n];
            // 删除左端点
            sum -= code[(r - k + i) % n];
        }
        return ans;
    }
};
// @lc code=end
