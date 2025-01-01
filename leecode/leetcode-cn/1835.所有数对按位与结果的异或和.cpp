/*
 * @lc app=leetcode.cn id=1835 lang=cpp
 *
 * [1835] 所有数对按位与结果的异或和
 */

// 既然叫“异或和”，我们猜测：“异或”相当于加法，“按位与”相等于乘法。
// 也就是 (a1 + a2 + a3) * (b1 + b2 + b3)
// 即 (a1 ^ a2 ^ a3) & (b1 ^ b2 ^ b3)
// 题设是展开式，答案是上式。
//
// 证明：以下变量都是一个二进制位：
// 列举 a = 0 或 a = 1 得知：(a & b) ^ ( a & c) = a & (b ^ c)，且按位与满足交换律。则有
// ① (a1 & b1) ^ (a1 & b2) = a1 & (b1 ^ b2)；
// ② (a1 & b1) ^ (a1 & b2) ^ (a1 & b3) = [a1 & (b1 ^ b2)] ^ (a1 & b3)
//  = a1 & [(b1 ^ b2) ^ b3] = a1 & (b1 ^ b2 ^ b3)
// ③ 同理，有
//  (a2 & b1) ^ (a2 & b2) ^ (a2 & b3) = a2 & (b1 ^ b2 ^ b3)
// 于是 ② ^ ③ = [a1 & (b1 ^ b2 ^ b3)] ^ [a2 & (b1 ^ b2 ^ b3)]
//  = [(b1 ^ b2 ^ b3) & a1] ^ [(b1 ^ b2 ^ b3) & a2] （按位与的交换律）
//  = (b1 ^ b2 ^ b3) & (a1 ^ a2)
// ...
// 对每一个二进制位，上面的法则都成立，那么对于所有二进制位（即整数）都成立。
//
// 如果先看下面的方法二，再看官方题解二，也很容易得到以上结论。

// 方法一
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        // bit_xor 位于 <functional> ，是一个函数对象，类似的还有 bit_and, bit_or, plus, minus
        int tot1 = reduce(arr1.begin(), arr1.end(), 0, bit_xor<int>());
        int tot2 = reduce(arr2.begin(), arr2.end(), 0, bit_xor<int>());
        return tot1 & tot2;
    }
};

// @lc code=start
// 官方题解一：https://leetcode.cn/problems/find-xor-sum-of-all-pairs-bitwise-and/solutions/728941/find-xor-sum-of-all-pairs-bitwise-and-by-sok6/
// 方法二：每个二进制位单独计算
// 对于 第 k 位：
// （1）arr1[i] & arr2[j] ，当且仅当两者的第 k 位都为 1 时，其按位与结果为 1 ，否则为 0 ；
// （2）异或运算 r1 ^ r2 ^ r3 ^ ... 中，其中每项都为 0 或 1。当 1 为奇数个时，结果为 1 ；当 1 为偶数个时，结果为 0 。
// 若 arr1 第 k 位有 cnt1 项为 1 ，arr2 有 cnt2 项为 1 ，
// 那么一共会产生 cnt1 * cnt2 个 “arr[i] 和 arr[j] 两者同时为 1” 的情况，
// 由（1）知，此时会产生 cnt1 * cnt2 个 1 来异或；
// 由（2）知，如果这些 1 是奇数个，结果为 1 ，反之为 0 .
class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        int m = arr1.size(), n = arr2.size(), ans = 0;
        // 依次确定每一位
        for (int k = 30; k >= 0; --k) {
            int cnt1 = 0;
            for (auto x : arr1) {
                if (x & (1 << k))
                    ++cnt1;
            }
            int cnt2 = 0;
            for (auto x : arr2) {
                if (x & (1 << k))
                    ++cnt2;
            }
            // 也等价于两者都为奇数
            if ((long long)cnt1 * cnt2 % 2 == 1)
                ans |= (1 << k);
        }
        return ans;
    }
};
// @lc code=end
