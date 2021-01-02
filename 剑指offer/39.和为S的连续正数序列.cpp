/*
题目描述
输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
*/

class Solution
{
 public:
  vector<vector<int>> FindContinuousSequence(int sum)
  { //贪心算法
    vector<vector<int>> res;
    int first = 1, last = 2; // 求first到last的和，不断增减first和last来调整
    while (last <= (sum + 1) / 2)
    { // 如果2*last-1>sum，那么不可能有first到last的和等于sum
      int tmp = (first + last) * (last - first + 1) / 2;
      if (tmp == sum)
      {
        vector<int> vec;
        for (int i = first; i <= last; i++)
          vec.push_back(i);
        res.push_back(vec);
        last++; // 从前往后寻找
      }
      else if (tmp > sum)
      {
        first++;
      }
      else
      {
        last++;
      }
    }
    return res;
  }
};