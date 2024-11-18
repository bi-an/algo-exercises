// 埃氏筛
// 时间复杂度：O(n log logn)
// 判断质数时间复杂度为 sum{n/p, 其中 p 是不超过 n 的质数} → n log logn，证明方法可以自行搜索。
// 可以计算一个较宽松的上界， sum{n/i, i = 1, 2, ..., n} = n sum{1/i, i = 1, 2, ..., n} → n logn。
class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n, true);
        int cnt = 0;
        for (int i = 2; i < n; ++i) {
            if (isPrime[i]) {
                ++cnt;
                // 步长为 i，质数 i 的所有倍数都是合数
                // 从 i*i 开始遍历即可，因为 k*i, 其中 k < i，已经被遍历过了
                if ((long long)i * i < n) {
                    for (int j = i * i; j < n; j+=i) {
                        isPrime[j] = false;
                    }
                }
            }
        }
        return cnt;
    }
};