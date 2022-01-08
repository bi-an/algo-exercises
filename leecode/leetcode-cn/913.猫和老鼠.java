// 极大极小博弈
// 参考：
//  https://leetcode-cn.com/problems/cat-and-mouse/solution/pythonjavajavascriptgo-zui-da-zui-xiao-b-fyt8/
//  https://www.zhihu.com/question/27221568/answer/140874499
// 注意：2*n 不足以判断平局，2*n^2 才能遍历完所有情景出现完全相同的情况，其中 n = graph.length，测试用例：
//  [[5, 7, 9], [3, 4, 5, 6], [3, 4, 5, 8], [1, 2, 6, 7], [1, 2, 5, 7, 9], [0, 1, 2, 4, 8], [1, 3, 7, 8], [0, 3, 4, 6, 8], [2, 5, 6, 7, 9], [0, 4, 8]]
//  [[2, 4, 6], [2, 5, 6, 7], [0, 1, 6, 8, 9], [4, 5, 7, 9], [0, 3, 6, 7, 8], [1, 3, 6, 7, 9], [0, 1, 2, 4, 5, 9], [1, 3, 4, 5, 8], [2, 4, 7, 9], [2, 3, 5, 6, 8]]
//  [[7], [2, 6, 8, 9], [1, 4, 5, 6, 7], [4, 5, 7], [2, 3, 5, 8], [2, 3, 4, 7], [1, 2, 9], [0, 2, 3, 5, 9], [1, 4, 9], [1, 6, 7, 8]]
class Solution {
    private int[][] graph;
    private Map<Integer, Map<Integer, Integer>> cache; // 减少重复计算

    // graph 是邻接表
    public int catMouseGame(int[][] graph) {
        this.graph = graph;
        cache = new HashMap<>();
        int value = minimax(0, 1, 2); // 老鼠先开始移动
        if (value == -1)
            return 1;
        if (value == 1)
            return 2;
        return 0;
    }

    // i: depth
    // m: mouse's position
    // c: cat's position
    // -1 表示鼠胜，1 表示猫胜，0 表示平局
    // 老鼠先开始
    // 递归应该倒序来看
    public int minimax(int i, int m, int c) {
        if (i > 2 * graph.length) // TODO 实际上， 2*n 次博弈不足以判定平局
            return 0; // 平局
        if (m == 0)
            return -1; // 老鼠进洞，鼠胜
        if (c == m)
            return 1; // 抓到老鼠，猫胜

        // 判断有没有相同的情形出现
        Map<Integer, Integer> memo = cache.getOrDefault(i, new HashMap<>()); // TODO i 可能出现多次吗？
        int key = m * graph.length + c; // 可以唯一标识 (m,c) 的情形
        if (memo.containsKey(key))
            return memo.get(key);

        int value;
        if (i % 2 == 0) { // 当前轮到老鼠
            value = 1;
            for (int x : graph[m]) {
                value = Math.min(value, minimax(i + 1, x, c));
                if (value == -1) // 这个值是由上一次猫的选择导致的结果，所以猫一定不会选择这个值
                    break; // α-β剪枝 (alpha-beta pruning)
            }
        } else { // 当前轮到猫
            value = -1;
            for (int x : graph[c]) {
                if (x == 0)
                    continue; // 猫不能进洞
                value = Math.max(value, minimax(i + 1, m, x));
                if (value == 1)
                    break;
            }
        }
        memo.put(key, value);
        cache.put(i, memo);
        return value;
    }
}
