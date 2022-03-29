/*
 * @Author: your name
 * @Date: 2022-03-29 21:38:03
 * @LastEditTime: 2022-03-29 21:59:10
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\693.交替位二进制数.cc
 */


// 方法一：模拟
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 题目假定 1 <= n <= 2^31-1
        while(n > 0) {
            int b = n % 2;
            n >>= 1;
            if (b == n % 2)
                return false;
        }
        return true;
    }
};


// 方法二：位运算
class Solution {
public:
    bool hasAlternatingBits(int n) {
        // 当且仅当相邻二进制位相异时， a 的末尾才全为 1.
        // 注意：高位的前导零没有意义.
        // 右移在高位补零不影响，但是左移将在末尾补零，会导致末尾原来如果为 0，
        // 那么会出现两个连续的尾缀 0，影响我们对相邻比特位的判断.
        // 注意：对二进制位直接操作，可能会导致数值溢出，所以类型设为 long.
        long a = n ^ (n >> 1);
        // 当且仅当 a 的末尾全为 1 ，那么 a + 1 才会产生进位，并且把原来的 1 全变成 0,
        // 这样 a & (a + 1) 则必为 0.
        return (a & (a + 1)) == 0;
    }
};