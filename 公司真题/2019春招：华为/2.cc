// 消除重复数字，结果为最大数字

#include <bits/stdc++.h>
using namespace std;

int main()
{
  string num, res;
  cin >> num;

  for (int i = 0; i < num.size(); i++)
  {
    char c = num[i];
    bool flag = true;

    for (int j = 0; j < res.size(); j++)
    {
      if (res[j] == c)
      {
        if (res[j + 1] > res[j])
        {
          res.erase(j, 1);
          res += c;
        }
        flag = false;
        break;
      }
    }
    if (flag)
      res += c;
  }

  cout << res << endl;

  return 0;
}