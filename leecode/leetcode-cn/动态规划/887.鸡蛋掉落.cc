// https://www.cnblogs.com/xym4869/p/12581145.html
// labuladong

/**
 * @brief 双蛋问题
 *        2个鸡蛋，100层楼，找出扔蛋恰好不碎的楼层，求最少测试次数
 * 
 * @ans 这是求最坏情况下的最少次数
 *      贪心算法，假设最优解为x，每次扔蛋都保证最优。
 *      第1次扔，剩下次数为x-1，最坏情况下，该蛋碎了，那么剩下的区间中只能线性探测，也就是该区间长度不得超过x-1
 *      第2次扔，需要探测的区间长度不得超过x-2，最多还需测试x-2次
 *      ...
 *      第x次扔，剩余区间为0
 *      于是，有 1+2+...+x >= 100，求最小的x
 *      => x = 14
 * 
 *     也就是，第一次在14层扔，第二次在14+13=27层扔，...
 */


// 作者：ikaruga
// 链接：https://leetcode-cn.com/problems/super-egg-drop/solution/887-by-ikaruga/
class Solution {
public:
    int calcF(int K, int T)
    {
        if (T == 1 || K == 1) return T + 1;
        return calcF(K - 1, T - 1) + calcF(K, T - 1);
    }

    int superEggDrop(int K, int N)
    {
        int T = 1;
        while (calcF(K, T) < N + 1) T++;
        return T;
    }
};
