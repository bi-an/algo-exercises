/*
 * @lc app=leetcode.cn id=1016 lang=cpp
 *
 * [1016] 子串能表示从 1 到 N 数字的二进制串
 */

namespace solution_1 {

// 暴力搜索
// 时间复杂度：O(min(m,n)⋅mlogmin(m,n))
// 空间复杂度：O(logn)

// 时间复杂度的计算：
//
// 简单来说：（1）假设 n 对应的二进制数有 k+1 个二进制位，那么 2ᵏ < n ≤ 2ᵏ⁺¹-1 ，我们可以估算 n ≈ (1~2)·2ᵏ 。
// （2）假设字符串能表示所有 k+1 位的二进制数，这些数一共有 2ᵏ 个，
// 由于这些二进制数都不相同，我们想象一个定长 k 的滑动窗口在字符串上滑动，
// 那么最好情况下，每次移动一个字符位得到一个新数，也就是该字符串长度至少为 2ᵏ+k-1 ≈ n/2 ，
// 即长度 m > n/2 ，得 n < m/2 ，也就是说，长度为 m 的字符串最多能表示 n/2 个数，。
// （3）如果字符串能表示所有 k+1 位的二进制数，那么少于 k+1 位的所有数也一定能表示，去掉若干高位即可（即右移）。
// 由此，长度为 m 的字符串最多能表示 n/2 个数。由于 m < 1000 ，所以最多能表示 2000 个数，
// 不论 n 实际多大，都会提前退出，循环不超过 2000 次。
//
// 精确计算：已知 2ᵏ < n ≤ 2ᵏ⁺¹-1 ，估算 n ≈ (1~2)·2ᵏ 。
// （1） [2ᵏ, n] 范围的数共有 n-2ᵏ+1 个，每个数占据 k+1 个二进制位：
// 我们想象一个定长 k+1 的滑动窗口在字符串上滑动，那么最好情况下，每次移动一个字符位得到一个新数，
// 该字符串要想得到 n-2ᵏ+1 个不同的数，至少需要 n-2ᵏ+1+(k+1-1) 长度。
// （2） [2ᵏ‌‌⁻¹, 2ᵏ‌‌⁻¹-1] 范围的数一共有 2ᵏ‌‌⁻¹ 个，每个数占据 k 个二进制位：
// 同上，这需要至少 2ᵏ‌‌⁻¹ 长度的字符串。
// （3） 二进制位少于 k 个的数，是 [2ᵏ‌‌⁻¹, 2ᵏ‌‌⁻¹-1] 范围内的子集，因为将其右移若干位即可得到。
// 综上，二进制字符串的长度至少要 max( n-2ᵏ+1, 2ᵏ‌‌⁻¹ ) ≈ n/2 。
// 也就是 n < 2m ，由于 m ≤ 1000，所以其能表示的数不会超过 2m = 2000 个。即使 n 的范围很大，循环次数也不会超过 2000 。
// 见题解：https://leetcode.cn/problems/binary-string-with-substrings-representing-1-to-n/solutions/2265097/san-chong-suan-fa-cong-bao-li-dao-you-hu-nmtq/
class Solution {
public:
    bool queryString(string s, int n) {
        for (int i = 1; i <= n; ++i) {
            auto bin = bitset<32>(i).to_string();
            bin = bin.substr(bin.find('1'));  // 去掉前导 0
            if (s.find(bin) == string::npos)
                return false;
        }
        return true;
    }
};

}  // namespace solution_1

namespace solution_2 {

class Solution {
public:
    bool queryString(string s, int n) {
        unordered_set<int> seen;
        int m = s.length();
        for (int i = 0; i < m; ++i) {
            int x = s[i] - '0';
            if (x == 0)
                continue;
            // 以每个 '1' 为窗口起点，然后尽可能扩展窗口
            // 易知，其中包含很多重复计算，因为短串很可能被长串包含过
            for (int j = i + 1; x <= n; ++j) {
                seen.insert(x);
                if (j == m)
                    break;
                x = (x << 1) | (s[j] - '0');  // 下一个待验证的数
            }
        }
        return seen.size() == n;
    }
};

}  // namespace solution_2

// @lc code=start
// 由方法一时间复杂度的分析，设 n 的二进制位长为 k+1 ，只需看 s 能否表示 k 和 k+1 长度的二进制数即可。
// 可以用 k 和 k+1 长度的滑动窗口。
// 进一步地，我们已经判断了 [2ᵏ, n] 区间，将其右移一位得 [2ᵏ‌⁻¹, ⌊n/2⌋]，也就是该区间的数也必然可以表示，
// 为了避免重复计算，我们的下一次检查范围可以进一步缩小为二进制位长为 k 的区间的剩余部分：[n/2+1, 2ᵏ-1] 。
// 时间复杂度：O(m) ，其中 m 是字符串长度。
class Solution {
public:
    bool queryString(string s, int n) {
        // 由于后面会计算 k-1 ，所以必须保证 k ≥ 1
        if (n == 1)
            return s.find('1') != string::npos;
        // built-in count leading zeros ，GCC 和 CLANG 编译器提供的内建函数，统计前导零的个数（包括符号位）。
        int m = s.length(), k = 32 - __builtin_clz(n);  // 即分析中的 k+1

        // 检查二进制位长为 width 的在 [lo, hi] 范围内的所有数能否被 s 表示
        auto check = [&](int lo, int hi, int width) {
            unordered_set<int> seen;
            // 每次掩去右数第 width-1 位
            // 掩码也可使用 ~(1 << (width - 1))，注意到，此时高位也变成了 1 ，但是按位与不影响结果。
            // int mask = ~(1 << (width - 1));
            int mask = (1 << (width - 1)) - 1;
            int x = stoi(s.substr(0, width), nullptr, 2);  // s 是二进制数
            // 第一个子串也需要判断是否合法
            for (int i = width - 1; i < m; ++i) {
                // 位运算相当于滑动窗口
                x = ((x & mask) << 1) | (s[i] - '0');
                if (x >= lo && x <= hi)
                    seen.insert(x);
            }
            return seen.size() == hi - lo + 1;
        };
        return check(1 << (k - 1), n, k) && check(n / 2 + 1, (1 << (k - 1)) - 1, k - 1);
    }
};
// @lc code=end
