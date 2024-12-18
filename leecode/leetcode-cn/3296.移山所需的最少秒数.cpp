// 题解：https://leetcode.cn/problems/minimum-number-of-seconds-to-make-mountain-height-zero/solutions/2925848/er-fen-da-an-pythonjavacgo-by-endlessche-myg4
// 方法一：最小堆模拟
// 时间复杂度：O(H*logn)，其中 H 是山的高度， n 是工人的人数
//            即 10^5 * log(10^4) = 10^5 * log(2^16) = 16*10^5
// 空间复杂度：O(n)，堆的大小始终为工人的人数
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // 每次选一个「工作后总用时最短」的工人，把山的高度降低 1
        // 存储每个工人此时的总用时，最大的总用时就是当前的总用时
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
            // 我们的目的是为了计算cur，但是因为每个工人的这三个值都不一样，所以需要都存下来
            auto [cur, x, t] = heap.top();
            heap.pop();
            ans = max(ans, cur);
            heap.push({cur + (long long)t * (x + 1), x + 1, t});  // 为下一次作准备
        }
        return ans;
    }
};

namespace solution_2 {
// 写法二：
// 记 t = workerTimes[i]
// S(x) = t + 2t + ... + x*t
// S(x+1) = t + 2t + ... + x*t + (x+1)t
// S(x+1) = S(x) + (x+1)t = S(x) + t*x + t
// 于是，我们可以将乘法改成加法，降低运行时间（加法效率比乘法高）
// 测试结果：这种写法反而比上面的写法效率低一点点（几十毫秒）
// 可能原因是，我们在 tuple 中第二个参数从 int 改成了 long long，
// 内存增加后，使用寄存器的个数变多，并且缓存命中率变低
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long ans = 0;
        priority_queue<tuple<long long, long long, int>, vector<tuple<long long, long long, int>>, greater<>> heap;
        for (auto t : workerTimes) {
            // x=1
            // S(1)=1
            heap.push({t, t, t});
        }
        while (mountainHeight--) {
            auto [sx, tx, t] = heap.top();
            heap.pop();
            ans = max(ans, sx);
            heap.push({sx + tx + t, tx + t, t});  // 下一次 x → x+1 ，所以 tx → t(x+1)
        }
        return ans;
    }
};
}  // namespace solution_2

namespace solution_3 {
// 方法二：数学 + 二分法
// 题解：https://leetcode.cn/problems/minimum-number-of-seconds-to-make-mountain-height-zero/solutions/2925848/er-fen-da-an-pythonjavacgo-by-endlessche-myg4
// 时间复杂度：O(nlog(h^2*maxT))，其中 h = H / n ，
//            最大时间为 n 最大时，此时 h 大概只有 10 左右，总时间为 10^4 * log(10^2 * 10^6) = 26 * 10^4
//            比最小堆解法快 10 倍左右。
// 空间复杂度：O(1)
class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long ans = 0;

        auto check = [&](long long m) -> bool {
            int h = mountainHeight;
            for (int t : workerTimes) {
                // 一元二次方程的求根公式计算出来的，第 m 秒该工人将山降低的高度 x
                h -= (int)((sqrt(1 + m / t * 8) - 1) / 2);  // 向下取整
                // 因为题目中，第 m 秒工人 i 将山降低的高度 x 必须是整数，也就是默认是向下取整的，
                // 所以最终得到的解不仅是可行解，并且是最优解。
                if (h <= 0)
                    return true;
            }
            return false;
        };

        // 假设每个人的 workerTimes[i] 都等于最慢的值，此时总耗时最大
        int max_t = ranges::max(workerTimes);
        // 每个人降低的山高度（因为效率相同），向上取整，防止遗漏
        int h = (mountainHeight - 1) / workerTimes.size() + 1;
        long long left = 0, right = (long long)h * (1 + h) / 2 * max_t;

        // 二分查找最少的秒数 m
        while (left + 1 < right) {
            long long m = (left + right) / 2;
            // 结合初始值可知，left 总是不符合条件的，right 总是符合条件的，也就是左开右闭区间
            // 故当 left 和 right 相邻，即 left + 1 = right 时，
            // (left, right] 可以直接得出 ans = right ，这就是循环的结束条件
            (check(m) ? right : left) = m;
        }

        return right;
    }
};

}  // namespace solution_3
