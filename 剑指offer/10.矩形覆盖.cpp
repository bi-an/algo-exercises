//本质是斐波那契数列
//n块砖，每块砖2*1方格
//从简单到复杂：n=1，则为1；n=2，则为2；
//3块砖，若第一个块砖竖着放，则剩下两块砖，这种情况之前已经考虑过了，即f(2);
//若第一块砖横着放，则必须在下方再横着放一块砖，剩下1块砖，即f(1);
//所以，f(3)=f(1)+f(2); f(n)=f(n-1)+f(n-2)

//假设有8块砖，第一块砖竖着放，则放法有f(7)；
//第一块砖横着放，则左下角还必须横着放一块，所以放法有f(6)；
//所以放法有f(8)=f(7)+f(6)，还是斐波那契数列。
/*       _     _ _ _ _ _ _ _ _
        |_|   |_|_|_|_|_|_|_|_|
        |_|   |_|_|_|_|_|_|_|_|
*/

//递归，运行400ms
class Solution
{
 public:
  int rectCover(int number)
  {
    if (number <= 0)
      return 0;
    if (number == 1)
      return 1;
    if (number == 2)
      return 2;

    return rectCover(number - 1) + rectCover(number - 2);
  }
};

//迭代，运行3ms
class Solution
{
 public:
  int rectCover(int number)
  {
    if (number <= 0)
      return 0;
    if (number == 1)
      return 1;
    if (number == 2)
      return 2;

    int first = 1, second = 2, third = 2;
    for (size_t i = 2; i < number; i++)
    {
      third = first + second;
      first = second;
      second = third;
    }
    return third;
  }
};

class Solution
{
 public:
  int rectCover(int number)
  {
    if (number <= 0)
      return 0;
    if (number == 1)
      return 1;
    int first = 1, second = 1;
    int res = 0;
    for (int i = 2; i <= number; i++)
    {
      res = first + second;
      first = second;
      second = res;
    }
    return res;
  }
};