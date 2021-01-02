/*
判断扑克牌的顺子，54张牌，2对大小王，大小王(设为0)可以代替任何数，J、Q、K为11、12、13.
*/
class Solution
{
 public:
  bool IsContinuous(vector<int> numbers)
  {
    if (numbers.empty() || numbers.size() > 13)
      return false;
    sort(numbers.begin(), numbers.end());
    int cnt_zero = 0;
    for (size_t i = 0; i < numbers.size(); i++)
    {
      if (numbers[i] != 0)
        break;
      cnt_zero++;
    }
    int cnt_lack = 0;
    for (size_t i = cnt_zero + 1; i < numbers.size(); i++)
    {
      int diff = numbers[i] - numbers[i - 1];
      if (diff == 0)
        return false;
      cnt_lack += diff - 1;
    }
    if (cnt_lack <= cnt_zero)
      return true;
    else
      return false;
  }
};