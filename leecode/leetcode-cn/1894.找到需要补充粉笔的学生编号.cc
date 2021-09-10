/*
 * @Author: your name
 * @Date: 2021-09-10 23:35:55
 * @LastEditTime: 2021-09-10 23:37:31
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\1894.找到需要补充粉笔的学生编号.cc
 */

// 模拟
// 时间复杂度O(n)，遍历两次，第一次累加O(n)，第二次找出结果O(n)
// 空间复杂度O(1)
class Solution {
public:
    int chalkReplacer(vector<int>& chalk, int k) {
        int i = 0, j = 0, n = chalk.size();
        long long total = std::accumulate(chalk.begin(), chalk.end(), 0ll); // 64 bit
        k %= total;
        while(k >= 0) {
            j = i++ % n;
            if(k < chalk[j])
                break;
            k -= chalk[j];
        }
        return j;
    }
};