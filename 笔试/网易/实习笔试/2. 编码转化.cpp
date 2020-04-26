#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string dec2bin(int dec)
{
  string res;
  while (dec)
  {
    int rem = dec % 2;
    res.push_back(rem + '0'); // 低位到高位
    dec /= 2;
  }
  return string(res.rbegin(), res.rend());
}

int bin2dec(string bin)
{
  int res = 0;

  // 从低位到高位
  int factor = 1;
  for (int i = bin.size() - 1; i >= 0; i--)
  {
    res = (bin[i] - '0') * factor + res;
    factor *= 2;
  }

  return res;
}

// 高位补零
// 每size分一组
string zeroFillHigh(string str, int size)
{
  // 高位补零
  int rem = str.size() % size;
  if (rem != 0)
  {
    for (int i = rem; i < size; i++)
    {
      str = "0" + str;
    }
  }
  return str;
}

bool isAllZero(string str)
{
  int res = true;
  for (int i = 0; i < str.size(); i++)
  {
    if (str[i] != '0')
    {
      res = false;
      break;
    }
  }
  return res;
}

string removeZeroHigh(string str, int size)
{
  int i = 0;
  string temp = str.substr(i, size);
  while (isAllZero(temp))
  {
    i += 5;
    temp = str.substr(i, size);
  }
  return str.substr(i, str.size() - i);
}

string dec2str32(int dec)
{
  string res;
  if (dec <= 9)
    res.push_back(dec + '0');
  else
    res.push_back(dec - 10 + 'A');
  return res;
}

string encode(string str)
{
  str = zeroFillHigh(str, 3); // 高位补零
  string bin;
  for (int i = 0; i < str.size(); i += 3)
  {
    string batch = str.substr(i, 3);   // 分组取值
    int decNum = atoi(batch.c_str());  // 转换为十进制数
    string binStr = dec2bin(decNum);   // 转换为二进制字符
    binStr = zeroFillHigh(binStr, 10); // 二进制高位补零
    bin += binStr;                     // 存储
  }
  bin = zeroFillHigh(bin, 5);   // 高位补零
  bin = removeZeroHigh(bin, 5); // 去除高位多余的零
  string dec5;
  for (int i = 0; i < bin.size(); i += 5)
  {
    string batch = bin.substr(i, 5);
    int decNum = bin2dec(batch);
    string str32 = dec2str32(decNum);
    dec5 += str32;
  }

  return dec5;
}

int main()
{

  // 每个函数测试

  string bin = dec2bin(10);
  int dec = bin2dec(bin);

  string str = zeroFillHigh(bin, 6);

  string str32 = dec2str32(31);

  cout << encode("150");

  return 0;
}