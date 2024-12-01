/*
 * @lc app=leetcode.cn id=2156 lang=cpp
 *
 * [2156] 查找给定哈希值的子串
 */

// @lc code=start
// 公式推导：https://leetcode.cn/problems/find-substring-with-given-hash-value/solutions/1249153/cha-zhao-gei-ding-ha-xi-zhi-de-zi-chuan-fi8jd/
//
// 注意到，递推式有减法，但是观察 hash 运算表达式，取模应该都是非负数，
// 故我们需要用到“同余”的概念，即
// 若 x < 0， y ≥ 0，有
//      x % m + m = y % m
// 模运算：https://leetcode.cn/circle/discuss/mDfnkW/
//
// 代码：https://leetcode.cn/problems/find-substring-with-given-hash-value/solutions/1239542/dao-xu-hua-dong-chuang-kou-o1-kong-jian-xpgkp/
class Solution {
public:
    string subStrHash(string s, int power, int modulo, int k, int hashValue) {
        int n = s.length();
        long long hash = 0, pk = 1;
        for (int i = n - 1; i >= n - k; --i) {
            hash = ((hash * power) % modulo + (s[i] - 'a' + 1)) % modulo;
            pk = pk * power % modulo;
        }
        int ans = n;
        if (hash == hashValue)
            ans = n - k;
        for (int i = n - k - 1; i >= 0; --i) {
            hash = (hash * power % modulo + (s[i] - 'a' + 1) - (s[i + k] - 'a' + 1) * pk % modulo + modulo) % modulo;
            h = ((h - (long long)(s[i + k] - 'a' + 1) * mult % modulo + modulo) * power + (s[i] - 'a' + 1)) % modulo;
            if (hash == hashValue)
                ans = i;
        }
        return s.substr(ans, k);
    }
};
// @lc code=end
