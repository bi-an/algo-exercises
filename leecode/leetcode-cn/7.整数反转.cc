/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-07-03 22:06:00
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-07-03 23:07:59
 * @FilePath: \practice\leecode\leetcode-cn\7.整数反转.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int re = x % 10;
            if (rev <= INT_MAX / 10 && rev >= INT_MIN / 10) {
                rev = rev * 10 + re;
            } else {
                return 0;
            }
            x /= 10;
        }
        return rev;
    }
};