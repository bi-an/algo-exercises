// 题解：https://leetcode-cn.com/problems/elimination-game/solution/wo-hua-yi-bian-jiu-kan-dong-de-ti-jie-ni-k2uj/
class Solution {
    public int lastRemaining(int n) {
        int head = 1, step = 1; // head表示最左边第一个数，step表示下一次移动的步长
        boolean left = true; // 表示从左边开始
        // 当只剩下1个数，那么head就是最终结果
        while (n > 1) { // n这里只表示当前数的个数
            if(left || n % 2 == 1) // head改变的条件：从左边开始删除；从右边开始，并且当前剩余数的个数奇数
                head += step;
            step <<= 1; // step *= 2;
            n >>= 1; // n /= 2;
            left = !left;
        }
        return head;
    }
}