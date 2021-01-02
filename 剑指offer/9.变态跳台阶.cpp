//f(n)=f(n-1)+f(n-2)+...+f(0)；解释：第一次跳1步，第一次跳2步，......第一次跳n步（这里f(0)=1).
//f(n-1)=f(n-2)+...+f(0)
//推导出：f(n)=2f(n-1)=2^2*f(n-2)=...=2^(n-1)*f(1)=2^(n-1), f(0)=1, f(1)=1.
//计算指数可以用位移运算或者指数

//f(0)=1（相当于第一次跳n步）; f(1)=1; f(2)=2; f(3)=f(2)+f(1)+f(1)=4;

//1. 递归计算指数，运行4ms, 占内存480k
class Solution
{
 public:
  int jumpFloorII(int number)
  {
    if (number == 0)
      return 0; //return 1;
    if (number == 1)
      return 1;

    return 2 * jumpFloorII(number - 1); //如果number>=1，根本不会进入jumpFloorII(0).
  }
};

//2. 循环，运行3ms
class Solution
{
 public:
  int jumpFloorII(int number)
  {
    if (number == 0)
      return 0;
    if (number == 1)
      return 1;

    int result = 1;
    for (size_t i = 1; i < number; i++)
    {
      result *= 2;
    }

    return result;
  }
};

//3. 位移运算, 运行4ms
class Solution
{
 public:
  int jumpFloorII(int number)
  {
    if (number == 0)
      return 0;
    if (number == 1)
      return 1;

    return 1 << (number - 1);
  }
};

//4. pow
class Solution
{
 public:
  int jumpFloorII(int number)
  {
    return pow(2, number - 1);
  }
};