// 首先这是一个大数问题，因为各个int在int可表示的范围，而拼接之后很可能超过int可表示的范围。
// 大数问题最好的方法是变成字符串。

// 接下来思考怎么拼接最小？
// 思路1：全排列之后，挑出最小的。 时间复杂度O(n!)
// 思路2：定义一种新的比较规则，两两拼接之后数值大的认为大，对于n和m，若nm>mn，则n>m.
// (因为拼接之后，字符串长度都一样，字符串按照ascii码比较即可)，然后排序(qsort)。 时间复杂度O(nlogn)
// 思路2的证明见《剑指offer》
class Solution
{
 public:
  string PrintMinNumber(vector<int> numbers)
  {
    if (numbers.empty())
      return string();
    vector<string> strs;
    for (int i = 0; i < numbers.size(); i++)
    {
      stringstream ss; //或者sprintf，注意itoa不是标准函数
      ss << numbers[i];
      strs.push_back(ss.str());
    }
    std::sort(strs.begin(), strs.end(), &Comp); //普通函数使用函数指针时，必须是static或者global函数
    string res;
    for (int i = 0; i < strs.size(); i++)
    {
      res += strs[i];
    }
    return res;
  }
  static bool Comp(string n, string m)
  { //static
    int res = (n + m).compare(m + n);
    if (res < 0)
      return true;
    else
      return false;
  }
};

// C语言版本
// strcpy, strcat, strcmp
int g_MaxNumberLength = 10;
char *g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char *g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int Comp(const void *n, const void *m)
{
  strcpy(g_StrCombine1, *(const char **)n);
  strcat(g_StrCombine1, *(const char **)m);

  strcpy(g_StrCombine2, *(const char **)m);
  strcat(g_StrCombine2, *(const char **)n);

  return strcmp(g_StrCombine1, g_StrCombine2);
}

class Solution
{
 public:
  string PrintMinNumber(vector<int> numbers)
  {
    // char **strNumbers = new char*[numbers.size()];
    // char **strNumbers=(char**)(new int[numbers.size()]);//因为int和指针占用内存大小相同（32bit机器），若为64bit机器，改成new long long
    // char **strNumbers=(char**)(new void*[numbers.size()]);//因为int和指针占用内存大小相同
    for (int i = 0; i < numbers.size(); i++)
    {
      strNumbers[i] = new char[g_MaxNumberLength + 1];
      sprintf(strNumbers[i], "%d", numbers[i]);
    }
    qsort(strNumbers, numbers.size(), sizeof(char *), Comp);
    string res;
    for (int i = 0; i < numbers.size(); i++)
    {
      res += string(strNumbers[i], strNumbers[i] + strlen(strNumbers[i]));
    }

    for (int i = 0; i < numbers.size(); i++) //一定要记得释放堆内存
      delete[] strNumbers[i];
    delete[] strNumbers;

    return res;
  }
};

// C语言版本
// strcpy, strcat, strcmp
int g_MaxNumberLength = 10;
char *g_StrCombine1 = new char[g_MaxNumberLength * 2 + 1];
char *g_StrCombine2 = new char[g_MaxNumberLength * 2 + 1];

int Comp(const void *n, const void *m)
{
  strcpy(g_StrCombine1, *(const char **)n);
  strcat(g_StrCombine1, *(const char **)m);

  strcpy(g_StrCombine2, *(const char **)m);
  strcat(g_StrCombine2, *(const char **)n);

  return strcmp(g_StrCombine1, g_StrCombine2);
}

class Solution
{
 public:
  string PrintMinNumber(vector<int> numbers)
  {
    //char **strNumbers = new char*[numbers.size()];
    char **strNumbers = (char **)(new void *[numbers.size()]); //因为int和指针占用内存大小相同
    for (int i = 0; i < numbers.size(); i++)
    {
      strNumbers[i] = new char[g_MaxNumberLength + 1];
      sprintf(strNumbers[i], "%d", numbers[i]);
    }
    qsort(strNumbers, numbers.size(), sizeof(char *), Comp);
    string res;
    for (int i = 0; i < numbers.size(); i++)
    {
      res += string(strNumbers[i], strNumbers[i] + strlen(strNumbers[i]));
    }

    for (int i = 0; i < numbers.size(); i++) //一定要记得释放堆内存
      delete[] strNumbers[i];
    delete[] strNumbers;

    return res;
  }
};