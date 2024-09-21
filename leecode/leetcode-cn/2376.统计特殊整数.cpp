/*
 * @lc app=leetcode.cn id=2376 lang=cpp
 *
 * [2376] 统计特殊整数
 */

// 题解来源：https://leetcode.cn/problems/count-special-integers/solutions/2916434/tong-ji-te-shu-zheng-shu-by-leetcode-sol-7qai/comments/2386766
class Solution {
public:
    int countSpecialNumbers(int n) {
        // 将 n 转化为一个数字数组
        vector<int> a;
        while (n > 0) {
            a.push_back(n % 10);
            n /= 10;
        }
        reverse(a.begin(), a.end());

        int ans = 0, m = a.size();
        // 总位数为 1~(m-1) 时，一定小于 n，故可求其全排列
        for (int i = 1; i < m; ++i) {
            ans += 9 * perm(9, i - 1);  // 固定首位，可选1~9
                                        // 剩下 i-1 位求排列（可选0~9，须排除首位）
        }

        // 总位数为 m 位
        ans += (a[0] - 1) * perm(9, m - 1);  // 固定首位，剩下位求排列数
                                             // 首位特殊，不能为0，所以单独计算
        // 逐位固定后续的位
        set<int> s = {a[0]};  // 为了去重
        for (int i = 1; i < m; ++i) {
            int count = 0;                    // 当前位可能取值的个数
            for (int j = 0; j < a[i]; ++j) {  // 第i位（i从0开始）不得超过a[i]
                if (s.find(j) == s.end()) {   // 该数字没有被高位占用
                    count++;
                }
            }
            // 可以从0~9选，但需要除去第0~i位，所以是10-i-1=9-i
            // 还剩下 m-i-1 位
            ans += perm(9 - i, m - i - 1) * count;
            // a[i] 本身
            if (s.find(a[i]) != s.end()) {
                // 达到最后一个特殊数字
                // 例如 82274，取到第 2 个 2 时，说明 1~82199 的数字都已经搜寻过了
                // 而 822xx 不符合条件，故再大也不符合条件了，已经逼近到可能的最大值
                return ans;
            }
            s.insert(a[i]);
        }
        return ans + 1;  // n 本身也是特殊数字，在上面的循环中没有被计入
    }

    // 计算排列数 P(n, k) = n! / (n-k)!
    int perm(int n, int k) {
        int res = 1;
        for (int i = 0; i < k; ++i) {
            res *= (n - i);
        }
        return res;
    }
};

// @lc code=end
