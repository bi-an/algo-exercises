#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m;
int input[500010];
int tree[500100];
int lowbit(int x)
{
  return x & -x;
}
void add(int x, int k)
{
  while (x <= n)
  {
    tree[x] += k;
    x += lowbit(x);
  }
}
int search(int x)
{
  int ans = 0;
  while (x != 0)
  {
    ans += tree[x];
    x -= lowbit(x);
  }
  return ans;
}
int main()
{
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> input[i]; // 注意，起始没有建树
  for (int i = 1; i <= m; i++)
  {
    int a;
    scanf("%d", &a);
    if (a == 1)
    {
      int x, y, k;
      scanf("%d%d%d", &x, &y, &k);
      // 差分数组思想
      // 初始化时，tree不需要真正保存差分数组
      // 只需要在执行改动操作时，动态保存相对于原tree的差异即可。
      // tree[x]保存的是相对input[x]的差异
      add(x, k);
      add(y + 1, -k);
    }
    if (a == 2)
    {
      int x;
      scanf("%d", &x);
      printf("%d\n", input[x] + search(x));
    }
  }
}