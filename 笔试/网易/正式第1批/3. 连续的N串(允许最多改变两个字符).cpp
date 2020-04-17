/*
作者：Jimmy5555
链接：https://www.nowcoder.com/discuss/221051
来源：牛客网
*/

#include <cstring>
#include <iostream>
using namespace std;

// 滑动窗口，双指针维护，窗口内最多两个非N字符
int main()
{
  int T;
  cin >> T;
  string s;
  while (T--)
  {
    cin >> s;
    int len = s.size();
    int flag = 2, i = 0, j = 0, ans = 0;
    while (j < len)
    {
      if (s[j] == 'N')
        j++;
      else
      {
        if (flag > 0)
        {
          flag--;
          j++;
        }
        else
        {
          ans = max(ans, j - i);
          while (flag == 0)
          {
            if (s[i] == 'N')
              i++;
            else
            {
              i++;
              flag++;
              break;
            }
          }
        }
      }
    }
    ans = max(ans, j - i);
    cout << ans << endl;
  }
  return 0;
}

// @Athor zzg
int maxN(string str)
{
  // if (str.empty()) return 0;
  int i = 0, j = 0; // 双指针控制滑动窗口，左闭右开区间
  int window = 2;   // 窗口内最多两个非N字符
  int maxLen = 0;
  while (i < str.size())
  {
    if (str[i] == 'N')
    {
      i++;
    }
    else if (window > 0)
    {
      i++;
      window--;
    }
    else
    {
      if (i - j > maxLen)
      {
        maxLen = i - j;
      }
      while (str[j] == 'N')
      {
        j++;
      }
      j++; // j++的意思是，从窗口中去掉一个非N字符，所以接下来window++
      window++;
    }
  }
  if (i - j > maxLen)
  { // 因为很可能else里面的maxLen没有来得及计算，所以，在循环外需要再判断一次
    maxLen = i - j;
  }
  return maxLen;
}
