// 这属于动态规划的范畴

//这是斐波那契的变种：f(n)=f(n-1)+f(n-2) //分类：最后一步跳一步，最后一步跳两步;或者说第一次跳1步，第一步跳2步
//注：排列组合不可用，因为求阶乘会溢出

//递归法
//运行：430ms
class Solution
{
 public:
  int jumpFloor(int number)
  {
    if (number == 0)
    {
      return 0;
    }
    if (number == 1)
    {
      return 1;
    }
    if (number == 2)
    {
      return 2;
    }
    return jumpFloor(number - 1) + jumpFloor(number - 2);
  }
};

//循环法
//运行：3ms
class Solution
{
 public:
  int jumpFloor(int number)
  {
    if (number <= 0)
      return 0;
    if (number == 1)
      return 1;
    if (number == 2)
      return 2;
    int first = 1, second = 2;
    int res = 0;
    for (int i = 3; i <= number; i++)
    {
      res = first + second;
      first = second;
      second = res;
    }
    return res;
  }
};

//扩展1：题目改成，青蛙一次可以跳1~n步，问总共有几种跳法？
//根据数学归纳法可以证明：f(n)=2^(n-1).
//--> 见“变态跳台阶”题。

//扩展2：如图：我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
//请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？
//--> 见“举行覆盖”题。
/*       _     _ _ _ _ _ _ _ _
        |_|   |_|_|_|_|_|_|_|_|
        |_|   |_|_|_|_|_|_|_|_|
*/