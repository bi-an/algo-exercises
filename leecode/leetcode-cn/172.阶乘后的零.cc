/*
 * @Author: your name
 * @Date: 2022-03-26 17:10:57
 * @LastEditTime: 2022-03-26 17:12:33
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\172.阶乘后的零.cc
 */


// 可以证明：如果质因子 a > b，那么 n! 中 a 的个数一定不超过 b 的个数。
// 证明参见官方题解。
class Solution {
    int num2 = 0, num5 = 0;
public:
    int trailingZeroes(int n) {
        for(int i = 1; i <= n; ++i) {
            factorize(i);
        }
        return min(num2, num5);
    }

    void factorize(int n) {
        while(n % 2 == 0) {
            n /= 2;
            num2++;
        }
        while(n % 5 == 0) {
            n /= 5;
            num5++;
        }
    }
};