class Solution {
    public int eatenApples(int[] apples, int[] days) {
        PriorityQueue<int[]> Q = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        int ans = 0, n = apples.length;

        for (int i = 0; i < n || !Q.isEmpty(); i++) {
            if (i < n)
                Q.add(new int[]{i + days[i], apples[i]});
            while (!Q.isEmpty() && Q.peek()[0] <= i) { // 移除腐烂的苹果
                Q.poll();
            }
            if (!Q.isEmpty()) {
                if (--Q.peek()[1] == 0)
                    Q.poll(); // 苹果吃完了
                ans++;
            }
        }

        return ans;
    }
}