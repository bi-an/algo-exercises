/*
 * @lc app=leetcode.cn id=1541 lang=cpp
 *
 * [1541] 平衡括号字符串的最少插入次数
 */

// @lc code=start
// @ref 官方题解：https://leetcode.cn/problems/minimum-insertions-to-balance-a-parentheses-string/solutions/391236/ping-heng-gua-hao-zi-fu-chuan-de-zui-shao-cha-ru-2/
// 括号匹配的问题一般使用栈解决，本题可以用计数代替栈
// 模拟。由于一个左括号对应两个连续右括号，所以维护左括号的个数更方便。
// 贪心算法：由于我们每次都在无法匹配的时候才插入，所以插入次数是最少的。
class Solution {
public:
    int minInsertions(string s) {
        int ans = 0, n = s.length();
        int i = 0, l = 0;  // l是左括号的计数
        while (i < n) {
            if (s[i] == '(') {
                ++l;
                ++i;
            } else {
                // 对于右括号，需要寻找左括号与之匹配
                if (l > 0) {  // 存在左括号与之匹配
                    --l;      // 消耗一个左括号
                } else {
                    ++ans;  // 没左括号与右括号匹配，插入一个左括号
                }
                // 需要保证下一个也是右括号
                if (i + 1 < n && s[i + 1] == ')') {
                    i += 2;  // 存在两个连续的右括号，匹配完毕，进行下一次匹配
                } else {
                    ++ans;  // 需要插入一个右括号
                    ++i;    // 匹配完毕，下一次从下一个字符开始
                }
            }
        }
        // 左括号可能没有匹配完
        ans += l * 2;
        return ans;
    }
};

namespace solution_2 {

/**
 * @file 1541.平衡括号字符串的最少插入次数.cc
 * @date 2020-11-14
 * @ref labulangdong
 *
 * 如果不及时将右括号数放入res暂存，则在今后遇到右括号时慢慢被减去时，need会慢一步到达-1，
 * 因为到达-1意味着结果陡增（left+1, right+2），而慢一步达到-1，则结果反而减少了1，
 * 导致最终所需要的括号总数变少（少了3）。例如：
 *              )   (   )   (   )   )       )
 * need     -1->1   3   2   3   2   1       0
 * res       0->1   1   1   2   2   2       2
 *
 * 实际如下
 *
 * need     -1->1   2   1   2   1   0   -1->1
 * res       0->1   2   2   3   3   3    2->4
 */

class Solution {
public:
    int minInsertions(string s) {
        // need为此后需要的右括号
        // res为已经插入的括号个数，可能同时包括'('和')'
        int res = 0, need = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                need += 2;
                if ((need & 1) == 1) {  // 奇数
                    res++;              // 插入一个右括号
                    need--;             // 所需右括号的个数变少一个，因为插入了一个
                }
            } else if (s[i] == ')') {
                need--;
                if (need == -1) {
                    res++;      // 插入一个左括号
                    need += 2;  // 需要匹配两个右括号
                }
            }
        }

        return res + need;
    }
};

}  // namespace solution_2

// @lc code=end
