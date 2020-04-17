// 题目：Procotol Buffer是谷歌的一种用于网络数据传输的序列化库，
// 其对整数变长编码，从低位向高位输出，每次输出一个字节，
// 含源数据信息7bit和最高位的标志位,最高位为1表示继续，0表示结束。

// 测试：

// 输入1：
// input:
// 	100 0XE70X070X660X7F
// output:
// 	0X64
// 	4
// 	999
// 	8

// 输入2：
// input:
// 	57727 0XFF0XC20X03
// output:
// 	0XFF0XC20X03
// 	12
// 	57727
// 	12

// 点评：应该将unValue右移，而不是将掩码左移
// 要先看清题意，先分析输入、输出的测数据，
// 本题的输出为"0X64"，占用缓冲区4个字节，而不是1个字节，也就是说写入的不是数值，而是acsii

// @Inputs:
//		unValue	待编码数字
//		nChars	缓冲区大小
// @outputs:
//		pOutput 将编码结果写入缓冲区
// @return
//		写入缓冲的字节数
int encode(unsigned int unValue, unsigned char *pOutput, int nChars)
{
  int resss = unValue;

  int maskLo = 0x7F;
  int nBytes = 0;
  for (int i = 0; unValue != 0; i++)
  {
    int byte = unValue & maskLo;
    nBytes += 4;
    pOutput[i * 4] = '0';
    pOutput[i * 4 + 1] = 'X';

    if ((unValue >> 7) != 0)
    {
      byte = byte | 0xA0;
    }

    if (byte < 16)
    {
      pOutput[i * 4 + 2] = '0';
      sprintf((char *)pOutput + i * 4 + 3, "%X", byte); //如果byte只有1位，如F，则写入的是F，而不是0F
    }
    else
      sprintf((char *)pOutput + i * 4 + 2, "%X", byte);

    unValue >>= 7; // 重要一步
  }
  return nBytes;
}

// @Inputs:
//		pInput 缓冲区
//		nChars 缓冲区大小
// @Outputs:
//		unValue 解码的int数值
// @return
// 		解码消耗的缓冲区内的字节数
int decode(unsigned char *pInput, int nChars, unsigned int &unValue)
{
  if (pInput == nullptr || nChars <= 0)
    return 0;
  int i = 0;
  unValue = 0;
  int byte = 0xA0;
  int j = 0; //记录右移次数
  for (; byte >= 0xA0 && i < nChars;)
  {
    byte = 0;
    i += 2;
    for (int ii = 0; ii < 2; ii++)
    {
      if (pInput[i] >= '0' && pInput[i] <= '9')
        byte = pInput[i] - '0' + byte;
      else
        byte = pInput[i] - 'A' + 10 + byte;
      i++;
      if (ii < 1)
        byte <<= 4;
    }
    unValue |= byte << (sizeof(int) - 1) * 8 + 1; // 每次读取7bit，放在最高7bit，之后右移。
    //unValue >>= 7;
    if (byte >= 0xA0)
    { // 防止过多移位，造成数据丢失
      unValue >>= 7;
      j += 7;
    }
  }

  while (j < sizeof(int) * 8 - 7)
  { // 一直移位至最低位为止
    unValue >>= 1;
    j++;
  }

  return i;
}

int main(int argc, const char *argv[])
{

  int value;
  unsigned char str[100];
  cin >> value;
  cin >> str;

  // 测试encode
  unsigned char out[100];
  int sz = encode(value, out, 100);
  printf("%s\n%d\n", out, sz);

  // 测试decode
  unsigned int unValue = 0;
  int size = decode(str, 100, unValue);
  cout << unValue << "\n" << size << "\n";

  return 0;
}
