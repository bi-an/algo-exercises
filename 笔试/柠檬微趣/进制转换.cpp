// @return 写入的字节数
int dec2hex(int dec, char *hex, int bufferSize)
{

  if (hex == nullptr)
    return 0;

  int maxIntBits = sizeof(int) * 2; // TODO: 要能够根据输入的数判断，而不是仅仅判断最大值
  if (bufferSize < maxIntBits + 1)
    return 0;

  int div = dec;
  int i = 0;
  char *cache = new char[bufferSize];
  for (; div != 0 && i < bufferSize; i++)
  {
    //rem = div - div / 16 * 16;
    int rem = div % 16;
    if (rem >= 0 && rem <= 9)
      cache[i] = rem + '0';
    else
      cache[i] = rem - 10 + 'A';
    div = div / 16;
  }
  if ((i & 0x1) != 0)
  {
    cache[i] = '0';
    i++;
  }

  // 倒过来
  for (int j = i - 1, k = 0; j >= 0; j--, k++)
  {
    hex[k] = cache[j];
  }

  hex[i] = '\0';

  delete cache;

  return i;
}

// 法二：sprintf
// 注意：要记得位数不足时前置补零
int dec2hex(int dec, char *hex, int bufferSize)
{

  if (hex == nullptr)
    return 0;

  int maxIntBits = sizeof(int) * 2; // TODO: 要能够根据输入的数判断，而不是仅仅判断最大值
  if (bufferSize < maxIntBits + 1)
    return 0;

  sprintf(hex, "%X", dec);
  int len = strlen(hex);
  if ((len & 0x1) == 1)
  {
    for (int i = len; i >= 0; i--)
    { // sprintf会在末尾插入'\0'，所以hex[len]=='\0'
      hex[i + 1] = hex[i];
    }
    hex[0] = '0';
    len++;
  }

  return len;
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

int bin2dec(string bin)
{
  int res = 0;

  // 从高位到低位
  for (int i = 0; i < bin.size(); i++)
  {
    res = res * 2 + bin[i] - '0';
  }

  return res;
}

string dec2bin(int dec)
{
  string res;
  while (dec)
  {
    int rem = dec % 2;
    res.push_back(rem + '0');
    dec /= 2;
  }
  return res;
}

string dec2str(int dec)
{
  string str = to_string(dec);
  return str;
}

int str2dec(string str)
{
  int dec = 0;
  for (int i = 0; i < str.size(); i++)
  {
    dec = dec * 10 + str[i];
  }
  return dec;
}

// pitch表示几进制, pitch必须小于等于9
int str2num(string str, int pitch)
{
  int res = 0;
  for (int i = 0; i < str.size(); i++)
  {
    res = res * pitch + str[i];
  }
  return res;
}

int hex2dec(string hex)
{
  int res = 0;
  for (int i = 0; i < hex.size(); i++)
  {
    if (hex[i] >= 'A' && hex[i] <= 'F')
      res = res * 16 + hex[i] - 'A' + 10;
    else if (hex[i] >= 'a' && hex[i] <= 'f')
      res = res * 16 + hex[i] - 'a' + 10;
    else
      res = res * 16 + hex[i] - '0';
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
}

string dec2str32(int dec)
{
  string res;
  if (dec <= 9)
    res.push_back(dec + '0');
  else
    res.push_back(dec + 'A');
  return res;
}
