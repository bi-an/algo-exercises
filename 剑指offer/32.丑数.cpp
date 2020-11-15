/*
把只包含质因子2、3和5的数称作丑数（Ugly Number）。
例如6、8都是丑数，但14不是，因为它包含质因子7。 
习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
*/

class Solution
{
 public:
  int GetUglyNumber_Solution(int index)
  {
    if (index <= 0)
      return 0;

    int *pUglyNumbers = new int[index];
    pUglyNumbers[0] = 1;
    size_t nextIndex = 1;
    int *pMultiply2 = pUglyNumbers; //指针，指向pUglyNumbers中的恰好大于 当前丑数*2 的数的位置
    int *pMultiply3 = pUglyNumbers;
    int *pMultiply5 = pUglyNumbers;

    while (nextIndex < index)
    {
      int min = Min(*pMultiply2 * 2, *pMultiply3 * 3, *pMultiply5 * 5);
      pUglyNumbers[nextIndex] = min;
      while (*pMultiply2 * 2 <= min)
        pMultiply2++;
      while (*pMultiply3 * 3 <= min)
        pMultiply3++;
      while (*pMultiply5 * 5 <= min)
        pMultiply5++;
      ++nextIndex;
    }
    int ugly = pUglyNumbers[nextIndex - 1];
    delete[] pUglyNumbers;
    return ugly;
  }

  int Min(int a, int b, int c)
  {
    int min = a < b ? a : b;
    min = min < c ? min : c;
    return min;
  }
};

// 直观而不高效的解法
// 对每个数都要判断
// @Athor zzg
class Solution
{
 public:
  int GetUglyNumber_Solution(int index)
  {
    if (index < 0)
      return 0;
    int order = 0;
    int num = 1;
    for (; order < index; num++)
    {
      if (IsUgly(num))
        order++;
    }
    return num;
  }

  // 如果能被2整除，就一直除以2；
  // 如果能被3整除，就一直除以3；
  // 如果能被5整除，就一直除以5；
  // 最后结果为1，就是丑数
  bool IsUgly(int num)
  {
    while (num % 2 == 0)
    {
      num /= 2;
    }
    while (num % 3 == 0)
    {
      num /= 3;
    }
    while (num % 5 == 0)
    {
      num /= 5;
    }
    if (num == 1)
      return true;
    else
      return false;
  }
};

// 改进：保存之前计算的丑数，避免在非丑数上浪费时间，空间换时间
// 如果数组中保存了若干丑数，那么之后的丑数则是在之前的丑数上 乘上2 或者 乘上3 或者 乘上5 得到的最小值。
// 保存之前乘上2、3、5的那个丑数的位置为T2、T3、T5，之后只需要在之后的丑数中查找并计算
// @Athor zzg
class Solution
{
 public:
  int GetUglyNumber_Solution(int index)
  {
    int *cache = new int[index];
    int pos = 0;
    cache[0] = 1;
    int T2 = 0, T3 = 0, T5 = 0;

    while (pos + 1 < index)
    {
      int t2 = 2 * cache[T2];
      int t3 = 3 * cache[T3];
      int t5 = 5 * cache[T5];

      int min = Min(t2, t3, t5);
      pos++;
      cache[pos] = min;
      if (t2 == min)
      {
        T2++;
      }
      if (t3 == min)
        T3++;
      if (t5 == min)
        T5++;
    }
    int res = cache[index - 1];
    delete[] cache;

    return res;
  }

  int Min(int a, int b, int c)
  {
    int min = a > b ? b : a;
    min = min > c ? c : min;

    return min;
  }
};
