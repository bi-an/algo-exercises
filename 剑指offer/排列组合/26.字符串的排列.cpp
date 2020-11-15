// 分成两步：
// (1)出现在第一位的所有可能字符；
// (2)固定第一位不变，求其他字符的排列。
// (3)对其他字符的排列，重复(1)和(2).
// 如果只有一个字符(begin=size)，打印。

// 正向来看，
// 固定(n-1)个字符，求剩下1个字符的排列；
// 固定(n-2)个字符，求剩下2个字符的排列：将剩下2个字符中，将第一位分别和其他位交换，打印，还原；
// 固定(n-3)个字符，求剩下3个字符的排列：将剩下3个字符中，将第一位分别和其他位交换，打印，还原；

//1. STL, 3ms
#include <algorithm>
vector<string> Permutation(string str)
{
  vector<string> res;
  if (str.empty())
    return res;
  sort(str.begin(), str.end());
  do
  {
    res.push_back(str);
  } while (next_permutation(str.begin(), str.end())); //STL的排列函数
  return res;
}

//2. 5ms
vector<string> Permutation(string str)
{
  vector<string> a;
  if (str.empty())
    return a;
  Permutation(a, str, 0);
  sort(a.begin(), a.end()); //按照字典序输出
  return a;
}
void Permutation(vector<string> &array, string str, int begin) //遍历第begin位的所有可能性
{
  //一次遍历的结束条件
  if (begin == str.size() - 1)
  {
    array.push_back(str);
  }
  for (int i = begin; i < str.size(); i++)
  {
    if (i != begin && str[i] == str[begin])
    {
      continue; //有与begin位重复的字符串不进行交换，跳过
    }
    swap(str[i], str[begin]);
    //当i==begin时，也要遍历其后面的所有字符
    //当i!=begin时，先交换，使第begin位取到不同的可能字符，再遍历后面的字符
    Permutation(array, str, begin + 1);
    swap(str[i], str[begin]); //为了防止重复的情况，还需要将begin处的元素重新换回来
  }
}

//3. 2ms
void Permutation(vector<string> &res, string str, int begin)
{
  int len = str.length();
  if (begin == len - 1)
    res.push_back(str);
  else
  {
    for (size_t i = begin; i < len; i++)
    {
      if (i == begin || str[i] != str[begin])
      {
        swap(str[begin], str[i]);
        Permutation(res, str, begin + 1);
        swap(str[begin], str[i]);
      }
    }
  }
}
vector<string> Permutation(string str)
{
  vector<string> res;
  if (!str.empty())
  {
    Permutation(res, str, 0);
    sort(res.begin(), res.end());
  }
  return res;
}

class Solution
{
 public:
  void Permutation(vector<string> &res, string str, int begin)
  {
    int len = str.length();
    if (begin == len - 1)
      res.push_back(str);
    else
    {
      for (size_t i = begin; i < len; i++)
      {
        if (i == begin)
        {
          Permutation(res, str, begin + 1);
        }
        else if (str[i] != str[begin])
        {
          swap(str[begin], str[i]);
          Permutation(res, str, begin + 1);
          swap(str[begin], str[i]);
        }
      }
    }
  }
  vector<string> Permutation(string str)
  {
    vector<string> res;
    if (!str.empty())
    {
      Permutation(res, str, 0);
      sort(res.begin(), res.end());
    }
    return res;
  }
};

// 相关题目
//
// 1. 输入一个含有8个数字的数组，判断：有没有可能把这8个数字分别放到正方体的8个顶点上，
// 使得正方体上3组相对面上的顶点之和相等。
//
// 思路：相当于先求8个数的排列，再找出符合条件的排列.
//
// 2. 8*8的国际象棋上摆放8个皇后，使其不能相互攻击，即任意两个不能处在同一行、同一列或者同一对角线上。
// 问有多少种摆放方法。
//
// 思路：用一个数组ColumnIndex[8]={0~7},数组第i个元素表示第i行皇后所处的列号，这样，不会处在同一行、同一列。
// 求0~7的全排列。
// 判断对角线：是否有 i-j==ColumnIndex[i]-ColumnIndex[j] 或者 j-i==ColumnIndex[i]-ColumnIndex[j].

// 3. 求所有字符的组合方式。
//
// 思路：分解
// (n, m)，从n个中取出m个，1<=m<=n.
// (n, m) = (n-1, m-1) + (n-1, m). 取出的m个数包含第一个数，取出的m个数不包含第一个数.
