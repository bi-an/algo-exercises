/*
 * @Author: your name
 * @Date: 2022-03-26 17:17:48
 * @LastEditTime: 2022-03-26 17:18:13
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\440. 字典序的第K小数字.java
 */
// 前缀树（十叉树）先序遍历到第 k 个即为答案。
// 由于 n 为上界，所以只能层序建立前缀树，因为 n 决定了前缀树的深度。
// 任何前缀都要先判断是否 大于 n 。
// 同一层中，相邻兄弟节点的前缀相差 1 。
// 不需要建立前缀树，因为有规律，我们根据规律找到第 k 个数即可。
// 顺序找到第 k 个数时间复杂度为 O(k)，依然超时。
// 同一层中，相邻兄弟节点的序号相差多少呢？显然等于以左兄弟为根的子树的节点数。
class Solution {
public:
    int findKthNumber(int n, int k) {
        long prefix = 1;//, ans = 0;
        // 注意到 k <= n，所以 k > 0 足以保证遍历前缀树时不会超出范围，
        // 所以不需要考虑 prefix 是否会超出 0 ~ 9 范围。
        while (k > 1) {
            //ans = prefix;
            int step = getStep(prefix, n);
            // cout << prefix << " " << step << endl;
            if (k <= step) {
                // 第 k 个数字在 prefix 子树上
                --k; // 计入 prefix 节点
                prefix *= 10; // prefix 移动到下一层最左节点
            } else {
                // 第 k 个数字不在 prefix 子树上
                k -= step;
                ++prefix; // prefix 移动到右兄弟节点
            }
        }
        return prefix;
    }

    // @return [prefix, next) 包含的节点数，其中 next 是 prefix （输入时的原始值）的最邻近右兄弟节点，
    //         换言之，即为 prefix 为根的子树的节点数。
    // 因为 prefix 不断乘上 10 ，有可能超出 int 范围，所以设为 long
    int getStep(long prefix, int n) {
        int step = 0;
        long next = prefix + 1; // 不包括 next
        while (prefix <= n) {
            step += next - prefix; // 层序遍历，计入当前层的节点数
            prefix *= 10; // prefix 移动到下一层的最左节点
            // 由于 step += next - prefix，也就是每层计算节点数的区间都为左闭右开 [prefix, next)，
            // 所以 next 上限为 n + 1
            next = min(next * 10, (long)n + 1); // next 始终处于最开始的那一层，乘上 10 是为了表明其高度在随之上升
        }
        return step;
    }
};