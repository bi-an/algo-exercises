// 题解：https://leetcode.cn/problems/minimum-number-of-seconds-to-make-mountain-height-zero/solutions/2925848/er-fen-da-an-pythonjavacgo-by-endlessche-myg4
// 方法一：最小堆模拟
// 时间复杂度：O(m*logn)，其中 m 是山的高度， n 是工人的人数
// 空间复杂度：O(n)，堆的大小始终为工人的人数
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // 每次选一个「工作后总用时最短」的工人，把山的高度降低 1
        priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<>> heap;  // 最小堆
        // 最小堆中是备选项，存储每个人的此次工作（将山的高度降低1）后的状态
        for (int t : workerTimes) {
            heap.push({t, 1, t});  // 含义见 while 中的注释
        }

        long long ans = 0;
        while (mountainHeight--) {
            // cur 该工人工作后的总工时
            // x 该工人工作后将山降低的高度
            // t 该工人的workerTimes[i]
            auto [cur, x, t] = heap.top();
            heap.pop();
            ans = max(ans, cur);
            heap.push({cur + (long long)t * (x + 1), x + 1, t});  // 为下一次作准备
        }
        return ans;
    }
};

// TODO:
// 方法二：二分法