/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-07-04 00:04:43
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-07-04 00:18:31
 * @FilePath: \practice\leecode\leetcode-cn\9.回文数.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// 方法一：比照完全反转之后的数字是否和原数相等即可。
// 也可以直接转化成字符串，两边朝中间进行字符串比较。
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;
        int rev = 0; // 反转的数字
        // 只需要验证一下反转的数字是否和原数相等即可
        int y = x;
        while (x != 0) {
            int re = x % 10;
            if (rev > INT_MAX / 10)
                return false; // 溢出，当然不可能等于原数
            rev = rev * 10 + re;
            x /= 10;
        }
        return rev == y;
    }
};

// 方法二：反转一半数字
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || x % 10 == 0 && x != 0)
            return false;
        int rev = 0; // 反转之后的数字
        while (x > rev) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }
        return x == rev || x == rev / 10;
    }
};
