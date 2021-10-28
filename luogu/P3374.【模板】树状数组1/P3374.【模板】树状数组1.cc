// https://www.luogu.com.cn/problem/solution/P3374
// 数据范围
// 对于 30% 的数据，1≤m≤10；
// 对于 70% 的数据，1≤n,m≤10^4;
// 对于 100% 的数据，1≤n,m≤5×10^5.

// 树状数组
// n个数据的树状数组的节点数为n
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
int n, m, tree[2000010]; // 根据数据范围，tree大小为5×10^5就足够了，亲测通过
int lowbit(int k)
{
    return k & -k;
}
void add(int x, int k)
{
    while (x <= n)
    {
        tree[x] += k;
        x += lowbit(x);
    }
}
int sum(int x)
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
    {
        int a;
        scanf("%d", &a);
        add(i, a);
    }
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1)
            add(b, c);
        if (a == 2)
            cout << sum(c) - sum(b - 1) << endl;
    }
}