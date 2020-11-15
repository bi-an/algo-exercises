/*一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。请写程序找出这两个只出现一次的数字。*/
// 要求：时间复杂度O(n)，空间复杂度O(1)

// 思路：如果这个数组中只有一个数字出现一次，其他都出现两次。
// 异或的性质：一个数异或本身等于0；从二进制位上看，两个数异或，会把所有不同的bit置1，相同bit置0.
// 异或满足交换律、结合律.
// 所以从头开始，所有数求异或，即a^b^c^...，所得结果恰好是那个只出现了一次的数。因为其他数出现了两次，一定会置为0.

// 所以，如果能把这两个数字分别分到两个数组，这两个数组中其他数字都出现了两次，那么就能按照上面的方法找出这个数。

// 分组方法：从头到尾，所有数求异或，由于有两个数不相等，所以结果一定不为0，而其他相同的数都会被抵消。
// 设异或结果中不为0的某个bit为1，记作第n bit，那么在这个比特位上，这两个不同的数的该位上一定相异
// 那么，按照第n bit是否为1的标准将数组分成两组，相同的数一定会进入同一组，这两个只出现一次的数一定会进入不同组。

// @Athor zzg

class Solution
{
 public:
  void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
  {
    if (!num1 || !num2 || data.empty())
      return;
    int tmp = data[0];
    for (size_t i = 1; i < data.size(); i++)
    {
      tmp = tmp ^ data[i]; //异或的结果=这两个不同数字的异或。因为相同数字异或结果为0
    }

    //找出右数第一个非0比特位
    int f_bit = (tmp ^ (tmp - 1)) & tmp; // 结果仅保留tmp中最右边的一个1，其他bit都置0

    vector<int> left, right;
    for (size_t i = 0; i < data.size(); i++)
    {
      if ((f_bit & data[i]) == 0)
        left.push_back(data[i]);
      else
        right.push_back(data[i]);
    }
    if (!left.empty())
    {
      tmp = left[0];
      for (size_t i = 1; i < left.size(); i++)
      {
        tmp ^= left[i];
      }
      *num1 = tmp; //第一个数
    }
    if (!right.empty())
    {
      tmp = right[0];
      for (size_t i = 1; i < right.size(); i++)
      {
        tmp ^= right[i];
      }
      *num2 = tmp; //第二个数
    }
  }
};

// @Athor zzg
class Solution
{
 public:
  void FindNumsAppearOnce(vector<int> data, int *num1, int *num2)
  {
    if (data.empty())
      return;
    int flag = data[0];
    for (int i = 1; i < data.size(); i++)
    {
      flag ^= data[i];
    }
    int pos = findLastBitOf1(flag);
    vector<int> left, right;
    for (int i = 0; i < data.size(); i++)
    {
      if (isBitOf1(data[i], pos))
        left.push_back(data[i]);
      else
        right.push_back(data[i]);
    }

    if (!left.empty())
    {
      int res1 = left[0];
      for (int i = 1; i < left.size(); i++)
      {
        res1 ^= left[i];
      }
      *num1 = res1;
    }
    if (!right.empty())
    {
      int res2 = right[0];
      for (int i = 1; i < right.size(); i++)
      {
        res2 ^= right[i];
      }
      *num2 = res2;
    }
  }

  // 右数第pos位是否是1, 从0开始
  bool isBitOf1(int num, int pos)
  {
    if ((num >> pos & 1) == 1)
      return true;
    else
      return false;
  }

  // 找到右数第一个1, 返回其位置(右数，从0开始)
  int findLastBitOf1(int num)
  {
    int pos = 0;
    while ((num & 1) != 1)
    {
      pos++;
      num >>= 1;
    }
    return pos;
  }
};