#include <iostream>
using namespace std;

// visual studio: x64或者x86
// long 4字节
// int 4字节
// long long 8字节

// gcc: x64
// long 8字节
// int 4字节
// long long 8字节

int main()
{
  long n, m; // 注意，这里要用long，用int会越界
  cin >> n >> m;

  long res = n * m / 2;

  cout << res;

  return 0;
}