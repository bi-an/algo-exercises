#include <iomanip>
#include <iostream>
using namespace std;

// pi = 6*arcsin(0.5)
// 再把arcsin泰勒展开
#define ORDER 100

double getPi()
{
  double ans = 0.5;
  double factor = 1;
  double x = 0.5;
  for (int i = 1; i < ORDER; i++)
  {
    int a = 2 * i - 1;
    int b = 2 * i;

    factor *= a * 1.0 / b;
    x = x * 0.5 * 0.5;
    ans += factor / (2.0 * i + 1) * x;
  }
  return 6 * ans;
}

int main()
{
  int n; // 如果使用std::to_string()，精度只能到8位（有效位数为8）
  cin >> n;

  std::cout << fixed << setprecision(n) << getPi() << std::endl; // fixed表示顶点，就是保留小数点n位

  return 0;
}