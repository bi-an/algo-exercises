
// 思路1: 如果已经排序好，那么取出中间数即可，即这个数是中位数。
// 利用快排的Partition，将数组元素一分为二，如果返回的index恰好等于n/2，那么取出即可；
// 如果返回的index > n/2，那么中位数在其左边；如果index < n/2，那么中位数在其右边。
// 时间复杂度：O(n)
// 分析：Partition的时间复杂度这里不是O(n), 而是每次从start遍历到end, 而且不需要重复遍历，所以一趟遍历vector即可找到。
class Solution
{
 public:
  bool m_InputValid = false;
  int MoreThanHalfNum_Solution(vector<int> numbers)
  {
    if (numbers.empty())
    {
      m_InputValid = false;
      return 0;
    }

    int middle = numbers.size() >> 1;
    int start = 0, end = numbers.size() - 1;
    int i = Partition(numbers, start, end);
    //while (i >= 0 && i != middle) {
    while (i != middle)
    {
      if (i > middle)
      {
        end = i - 1;
        i = Partition(numbers, start, end);
      }
      else
      {
        start = i + 1;
        i = Partition(numbers, start, end);
      }
    }
    int res = numbers[i];
    if (!CheckMoreThanHalf(numbers, res))
    {
      res = 0;
    }
    return res;
  }

  int Partition(vector<int> &numbers, int start, int end)
  {
    //if(numbers.size()<=1 || start<0 || end<start || end>=numbers.size()) return -1;
    //if (start < 0 || end < start || end >= numbers.size()) return -1;
    if (end == start)
      return start; //为了提高性能，实际上注释掉一样。
    int j = rand() % (end - start + 1) + start;
    swap(numbers[j], numbers[end]);
    int small = start - 1;
    for (int i = start; i < end; i++)
    {
      if (numbers[i] < numbers[end])
      {
        ++small;
        if (i != small)
        {
          swap(numbers[i], numbers[small]);
        }
      }
    }
    ++small;
    swap(numbers[small], numbers[end]);
    return small;
  }

  bool CheckMoreThanHalf(const vector<int> &numbers, int number)
  {
    if (numbers.empty())
      return false;
    int times = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
      if (number == numbers[i])
        times++;
    }
    bool res = false;
    if (times * 2 > numbers.size())
      res = true;
    return res;
  }
};

// 思路2：要找的数比其他所有数的出现次数都要多。
// 遍历数组时，可以保存两个数，数字digit和该数出现的次数times
// 当下一个数字等于digit，则times+1；否则times-1。
// 当times=0时，那么要保存下一个数字，并把times设为1。
// 要找的数比其他所有数的出现次数都要多，那么要找的数肯定是最后一次把times设为1时对应的数。
// 注意要判断是否超过一半次数
// 时间复杂度：O(n)
class Solution
{
 public:
  bool m_InputValid = false;
  int MoreThanHalfNum_Solution(vector<int> numbers)
  {
    if (numbers.empty())
      return 0;
    int digit = numbers[0], times = 1;
    for (int i = 1; i < numbers.size(); i++)
    {
      if (times == 0)
      {
        digit = numbers[i];
        times = 1;
      }
      else if (numbers[i] == digit)
        times++;
      else
        times--;
    }
    int res = 0;
    if (CheckMoreThanHalf(numbers, digit))
      res = digit;
    return res;
  }

  bool CheckMoreThanHalf(const vector<int> &numbers, int number)
  {
    if (numbers.empty())
      return false;
    int times = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
      if (number == numbers[i])
        times++;
    }
    if (2 * times > numbers.size())
      return true;
    return false;
  }
};

//此方法好像有误：当输入{1,2,3,2,2,2,4,3}时，应该输出0，实际却输出2.
class Solution
{
 public:
  int MoreThanHalfNum_Solution(vector<int> numbers)
  {
    if (numbers.empty())
      return 0;
    int digit = numbers[0], times = 1, flag = 0;
    for (size_t i = 1; i < numbers.size(); i++)
    {
      flag = 0;
      if (numbers[i] == digit)
        times++;
      else
      {
        times--;
        if (times == 0)
        { //times--之后立马判断，与法2不一样
          flag = 1;
          digit = numbers[i];
          times = 1;
        }
      }
    }
    if (times <= 1 && flag == 1)
      return 0;
    return digit;
  }
};
