// 题目：
// 数字以01234567891011121314...的格式排列。在这个序列中，
// 第5位（从0开始计）是5，第13位是1，第19位是4。求任意第n位对应的数字。

// 注意:这个数列是0,1,2,...,9,10,11,...构成的序列

// n位的数总共有多少个
int CountOfIntegers(int bits)
{
  if (bits <= 0)
    return 0;
  if (bits == 1)
    return 10;

  int count = pow(10, bits - 1);
  return 9 * count;
}

// n位的第一个数字
int BeginNumber(int bits)
{
  if (bits <= 0)
    return -1;
  if (bits == 1)
    return 0;
  return (int)(pow(10, bits - 1));
}

int DigitAtIndex(int index)
{
  if (index < 0)
    return -1;
  int bits = 1;
  int numsOfNbits = CountOfIntegers(bits);
  while (numsOfNbits <= index)
  {
    index -= bits * numsOfNbits;
    bits++;
    numsOfNbits = CountOfIntegers(bits);
  }

  int num = BeginNumber(bits);
  int div = index / bits;
  int rem = index % bits;
  num += div;
  for (int i = 0; i < bits - rem - 1; i++)
  {
    num /= 10;
  }
  return num % 10;
}