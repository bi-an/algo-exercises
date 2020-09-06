// 整数反转求和

#include <bits/stdc++.h>
using namespace std;

int getReverseNum(string n)
{
  int x = 0;
  for (int i = n.size() - 1; i >= 0; i--)
  {
    x = 10 * x + (n[i] - '0');
  }
  return x;
}

int main()
{
  string x, y;
  cin >> x >> y;

  cout << getReverseNum(x) + getReverseNum(y) << endl;

  return 0;
}