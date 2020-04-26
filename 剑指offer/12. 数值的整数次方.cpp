/*数值的整数次方

//注意：判断两个浮点数相等，不能直接用==，因为浮点数有精度范围，应该用 abs(double1-double2)<1e-5等等。

版权声明：本文为博主原创文章，未经博主允许不得转载。 https://blog.csdn.net/budf01/article/details/76203485 
题目描述
给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。
解题思路
库函数中有幂函数pow(x,y)，如果你直接return pow(base,exponent);也能通过测试用例，但估计offer无缘了。
为了降低时间复杂度，使用迭代：
如果n为偶数，a^n=a^(n/2)*a(n/2)；
如果n为奇数，a^n=a^(n/2)*a(n/2)*a；
n/2可以用右移1位得到；
此外，本题还要考虑以下几点：
exponent=0时，结果为1；
base趋近于0时，结果为0；
base趋近于1时，结果为1；
base趋近于-1时，指数为奇数时结果为-1，指数为偶数时结果为1；
exponent<0时，结果为(1/base)^(-exponent);
*/
class Solution
{
 public:
  double Power(double base, int exponent)
  {
    if (exponent == 0)
      return 1.0;

    if (fabs(base) < 1e-5)
      return 0.0;

    if (fabs(base - 1) < 1e-5)
      return 1;

    if (fabs(base + 1) < 1e-5)
      return exponent % 2 ? -1 : 1;

    if (exponent < 0)
    {
      base = 1.0 / base;
      exponent = -exponent;
    }

    double res = 1.0;
    while (exponent)
    {
      if (exponent % 2)
      {
        res *= base;
      }

      base *= base;
      exponent >>= 1;
    }
    // while (exponent) {
    //     if (exponent % 2 != 0) {
    //         res *= base;
    //         exponent--;
    //     }
    //     else {
    //         base*=base;
    //         exponent>>=1;
    //     }
    // }
    return res;
  }
};

//2、全面但不高效的解法
//考虑点：当指数为负数时，如果采用a^(-n)=1/a^n计算，那么底数为0时，会出错；另外0^0没有意义，可以返回1，也可以返回0；这两种都属于错误输入。
class Solution
{
 public:
  bool invalidInput = false;
  double Power(double base, int exponent)
  {
    if (fabs(base) < 1e-5 && exponent <= 0)
    {
      invalidInput = false;
      return 0;
    }
    double res = 1;
    int flag = 1;
    if (exponent < 0)
      flag = -1;
    for (int i = 0; i < flag * exponent; i++)
    {
      res *= base;
    }
    invalidInput = true;
    if (exponent < 0)
      res = 1.0 / res;
    return res;
  }
};

//3、高效的解法，
//  a^n = a^(n/2)*a^(n/2), 当n为偶数;
//  a^n = a^(n/2)*a^(n/2)*a, 当n为奇数。
//这个公式可以很方便地用递归实现。
class Solution
{
 public:
  double Power(double base, int exponent)
  {
    if (exponent == 0)
      return 1;
    if (exponent == 1)
      return base;
    //if (exponent == -1) return 1.0 / base;
    int flag = 1;
    if (exponent < 0)
      flag = -1;
    double result = Power(base, flag * exponent / 2); //这里不能用exponent>>=1，因为对于负数，不断右移，会达到-1之后不再变化，陷入死循环
    result *= result;
    if ((exponent & 0x1) == 1) //注意：==优先级比&高
      result *= base;
    if (exponent < 0)
      result = 1.0 / result;
    return result;
  }
};

// 注：循环并不会比递归效率高，只是因为循环经常可以减少不必要的计算，如Fibonacci
// 注意：-3右移一位，结果是-2，不是-1，要从二进制位来看。-9右移一位是-5，但是-9/2=-4.(VS编译环境下)
class Solution
{
 public:
  //去掉注释，则安全性加强。
  //bool g_ValidInput=true;
  double Power(double base, int exponent)
  {
    //if(base == 0 && exponent <=0) {g_ValidInput=false; return 1;}
    if (exponent == 0)
      return 1;
    if (exponent == 1)
      return base;
    if (exponent == -1)
      return 1.0 / base; // 若exponent为负数，不断右移，最终到达-1

    double result = Power(base, exponent >> 1); // 这里如果是exponent/2，则结果不正确
    result *= result;

    if ((exponent & 0x1) == 1)
      result *= base; // 这是因为如果exponent是奇数，不断右移，即使是负数，会不断向-inf方向取整，例如-9，不断右移变成-5,-3,-2,-1,
    // 这样最终一定会到达-2, 正好多乘了一个base^-1

    return result;
  }
};