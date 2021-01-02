class Solution
{
 public:
  Solution() : index(0)
  {
    for (int i = 0; i < 256; i++)
      pos[i] = -1;
  }
  //Insert one char from stringstream
  void Insert(char ch)
  {
    if (pos[ch] == -1)
      pos[ch] = index;
    else if (pos[ch] >= 0)
      pos[ch] = -2;
    ++index;
  }
  //return the first appearence once char in current stringstream
  char FirstAppearingOnce()
  {
    char ch = '#';
    int minIndex = std::numeric_limits<int>::max();
    for (int i = 0; i < 256; i++)
    {
      if (pos[i] >= 0 && pos[i] < minIndex)
      {
        ch = (char)i;
        minIndex = pos[i];
      }
    }
    return ch;
  }

 private:
  // pos[i]: i表示字符的ascii码
  // pos[i]=-1: 该字符没有出现
  // pos[i]=-2: 该字符不止出现一次
  // pos[i]>=0: 该字符只出现了一次
  int pos[256]; // 下标i对应的字符 (char)i 在字符流中的位置
  int index;    //记录字符流的下个位置
};

// 测试代码
int main()
{

  Solution sol;
  string str = "google";
  for (int i = 0; i < str.size(); i++)
  {
    sol.Insert(str[i]);
    cout << sol.FirstAppearingOnce() << " ";
  }

  return 0;
}