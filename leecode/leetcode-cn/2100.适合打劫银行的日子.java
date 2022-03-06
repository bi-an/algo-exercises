// 动态规划
// 所谓动态规划，就是状态集合，并且这些状态能够从临近状态转移过来。
class Solution {
  public List<Integer> goodDaysToRobBank(int[] security, int time) {
    List<Integer> ans = new ArrayList<>();
    int n = security.length;
    if (n < time * 2 + 1)
      return ans;
    int[] left = new int[n], right = new int[n];
    for (int i = 0, j = n - 1; i < n; i++, j--) {
      if (i > 0 && security[i] <= security[i - 1]) {
        left[i] = left[i - 1] + 1;
      }
      if (j < n - 1 && security[j] <= security[j + 1]) {
        right[j] = right[j + 1] + 1;
      }
    }
    for (int i = 0; i < n; i++) {
      if (left[i] >= time && right[i] >= time)
        ans.add(i);
    }
    return ans;
  }
}