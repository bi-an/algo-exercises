class Solution {
    public int[] loudAndRich(int[][] richer, int[] quiet) {
        int n = quiet.length;
        // 用邻接表表示有向图，由没钱的人指向更有钱的人
        // 因为逻辑自洽，所以这是一个无环图
        List<Integer>[] g = new List[n];
        for (int i = 0; i < n; i++)
            g[i] = new ArrayList<>();

        for (int[] r : richer) {
            g[r[1]].add(r[0]);
        }

        int[] ans = new int[n];
        Arrays.fill(ans, -1);

        // dfs遍历
        // 其实这是一个森林
        for (int i = 0; i < n; i++)
            dfs(i, g, quiet, ans);

        return ans;
    }

    // dfs每次能够遍历一棵树
    public void dfs(int x, List<Integer>[] g, int[] quiet, int[] ans) {
        // 这棵树已经遍历过，答案已经找到了
        if (ans[x] != -1)
            return;

        ans[x] = x;
        // 遍历 x 的邻居
        for (Integer y : g[x]) {
            dfs(y, g, quiet, ans);
            if (quiet[ans[y]] < quiet[ans[x]])
                ans[x] = ans[y];
        }
    }
}
