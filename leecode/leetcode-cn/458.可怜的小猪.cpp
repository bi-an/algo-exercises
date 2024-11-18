// @ref https://leetcode-cn.com/problems/poor-pigs/solution/geekplayers-leetcode-ac-qing-xi-yi-dong-0kc15/
class Solution
{
 public:
  int poorPigs(int buckets, int minutesToDie, int minutesToTest)
  {
    return (int)ceil(
        log(buckets) / log((double)minutesToTest / minutesToDie + 1));
  }
};