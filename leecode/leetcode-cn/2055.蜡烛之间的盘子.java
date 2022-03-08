class Solution {
  public int[] platesBetweenCandles(String s, int[][] queries) {
    int n = s.length();
    // 左右最近的蜡烛位置
    int[] left = new int[n], right = new int[n];
    // 前缀和：disk[i] 表示 [0,...,i-1] 的盘子个数
    int[] disk = new int[n + 1];

    for (int i = 1; i <= n; i++) {
      if (s.charAt(i - 1) == '*') {
        disk[i] = disk[i - 1] + 1;
      } else {
        disk[i] = disk[i - 1];
      }
    }

    int curLeft = -1, curRight = n;
    for (int i = 0; i < n; i++) {
      if (s.charAt(i) == '|')
        curLeft = i;
      if (s.charAt(n - 1 - i) == '|')
        curRight = n - 1 - i;
      left[i] = curLeft;
      right[n - 1 - i] = curRight;
    }

    int[] ans = new int[queries.length];
    for (int i = 0; i < queries.length; i++) {
      // 边界情况：
      // l == n || r == -1 || l > r
      int l = right[queries[i][0]], r = left[queries[i][1]];
      ans[i] = disk[r + 1] - disk[l];
      // 防止 l > r，因为前缀和是单增的，所以这样判断即可
      if (ans[i] < 0)
        ans[i] = 0;
    }

    return ans;
  }
}