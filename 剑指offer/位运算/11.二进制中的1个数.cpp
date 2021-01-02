//死循环解法
//验证最后一位是否为1，再右移，再验证最后一位......
//当n为负数，那么右移是在前面补1，而不是补0
class Solution
{
 public:
  int NumberOf1(int n)
  {
    int cnt = 0;
    while (n)
    {
      if (n & 1 == 1)
        cnt++;
      n >>= 1;
    }
    return cnt;
  }
};

//解法1：
//改进，不右移n，先把1与n按位与判断最后一位；再把1左移一位之后与n按位与，判断次末位；......
//效率分析： 对32bit的数，就要循环32次
class Solution
{
 public:
  int NumberOf1(int n)
  {
    int cnt = 0;
    unsigned int flag = 1; //最高位不表示符号位
    while (flag)
    {
      if (n & flag)
        cnt++;
      flag = flag << 1;
    }
    return cnt;
  }
};

//解法2：
//规律：一个数减去1，再与原来的数按位与，则把该数最右边的1变成0。（其他位不变）
//效率分析：该数中有几个1bit位，就循环几次。
class Solution
{
 public:
  int NumberOf1(int n)
  {
    int cnt = 0;
    while (n)
    {
      cnt++;
      n &= (n - 1);
    }
    return cnt;
  }
};

//相关题目：
// 1. 判断一个数是否是2的整数次方？ 答：如果是，则它的二进制位只有1个1
// 2. 两个数m和n，判断需要改变n中的多少位，才能得到m？
//	答(1)：将m和n按位或，计算结果中1的位数，再减去n中的位数。
//	答(2)：将m和n异或，计算结果中1的位数。（不一样的bit位，异或结果才为1）
