// 哈希表计数 + 懒惰更新
// 没有优化内存
class Solution {
  public int bestRotation(int[] nums) {
      int n = nums.length;
      Map<Integer, Integer> cnt = new HashMap<>();
      int score = 0;
      for(int i = 0; i < n; ++i) {
          int d = i - nums[i];
          cnt.put(d, cnt.getOrDefault(d, 0) + 1);
          if (d >= 0)
              ++score;
      }
      // k = 0 时的初始值
      int maxScore = score, ans = 0;
      for(int k = 0; k < n - 1; k++) {
          int d = k - nums[k]; // 第 k 次的 d[start]
          if ( d < k && d + n >= k + 1)
              ++score; // 第 k + 1 时的分数
          // 更新 cnt
          // 因为 d[start] 改变了（其他元素没有变），所以需要更新 cnt
          cnt.put(d + n, cnt.getOrDefault(d + n, 0) + 1); // 加入了一个 d + n
          cnt.put(d, cnt.get(d) - 1); // 去掉了一个 d
          // 第 k 次时 d == 阈值 k 的得分数（即个数）需要减去
          score -= cnt.getOrDefault(k, 0); // 第 k + 1 时的分数
          if (score > maxScore) {
              maxScore = score;
              ans = k + 1; // 因为 score 是第 k + 1 的分数
          }
      }
      return ans;
  }
}

// 哈希表计数 + 懒惰更新
// 内存优化了 2/3
class Solution {
  public int bestRotation(int[] nums) {
      int n = nums.length;
      int[] cnt = new int[n];
      int score = 0;
      for (int i = 0; i < n; ++i) {
          int d = i - nums[i];
          if(d >= 0) {
              ++score; // k = 0 时的初始分数
              ++cnt[d]; // d < 0 以及 d >= n 时不需要统计
          }
      }
      // 第 0 次的初始值
      int maxScore = score, ans = 0;
      for(int k = 0; k < n - 1; ++k) {
          int d = k - nums[k]; // 第 k 次的 d[start]
          // 第 k 次判别阈值为 k
          // 第 k + 1 次的判别阈值为 k + 1
          // 注意到 0 <= d,k <= n - 1，其实 d + n >= k + 1 是必然成立的
          if (d < k /* && d + n >= k + 1 */)
              ++score; // 第 k + 1 次的分数
          /// 更新 cnt
          // 其实，这里对 d 的判断只是为了降低内存空间，如果我们统计所有的 d 的取值的个数，
          // 那么直接有以下两步就可以了：++cnt[d + n]; --cnt[d];
          if (d < 0)
              ++cnt[d + n];
          else
              --cnt[d];
          score -= cnt[k]; // 第 k + 1 次的分数
          if (score > maxScore) {
              maxScore = score;
              ans = k + 1; // 因为 score 是第 k + 1 次的分数
          }
      }
      return ans;
  }
}