// 右数第pos位是否是1, 从0开始
bool isBitOf1(int num, int pos)
{
  if (num >> pos & 1 == 1)
    return true;
  else
    return false;
}

// f_bit得到num最右边的1,其他bit位都是0
int f_bit = (num ^ (num - 1)) & num;

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