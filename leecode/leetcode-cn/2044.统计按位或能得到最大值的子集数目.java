// 回溯法
// 时间复杂度：O(2^n)，每个元素可取可不取。
// 空间复杂度：O(n)，探索最大深度为 n.
class Solution {
  int maxVal = Integer.MIN_VALUE;
  int[] nums;
  int cnt = 0;

  public int countMaxOrSubsets(int[] nums) {
      this.nums = nums;
      backtrace(0, 0);
      return cnt;
  }

  public void backtrace(int start, int curVal) {
      for (int i = start; i < nums.length; ++i) {
          int val = curVal | nums[i];
          if (val > maxVal) {
              cnt = 1;
              maxVal = val;
          } else if (val == maxVal) {
              ++cnt;
          }
          backtrace(i + 1, val);
      }
  }
}

// 位运算
// 思路：题中取值范围 1 <= nums.length <= 16，只有 16 种取值，可以使用一个 int 的 16 个 比特位表示，
// 比特位为 1 表示选择这个数，0 表示不选择这个数，表现为这个 int 的某个取值。
// 所有情况一共有 2^n - 1 种，我们可以从 int 的 n bit 全为 0 遍历到全为 1，这样就囊括了所有情况。
// 时间复杂度：O(n * 2^n)
// 空间复杂度：O(1)
class Solution {
  public int countMaxOrSubsets(int[] nums) {
    int cnt = 0, maxOr = 0;
    // 遍历 2^n - 1 种情况
    for(int i = 0; i < 1 << nums.length; ++i) {
      int curOr = 0;
      // 查看第 j 位是否为 1（是否被选中）
      for(int j = 0; j < nums.length; ++j) {
        if(((i >> j) & 1) == 1)
          curOr |= nums[j];
      }
      if(curOr > maxOr) {
        maxOr = curOr;
        cnt = 1;
      } else if(curOr == maxOr) {
        ++cnt;
      }
    }
    return cnt;
  }
}
