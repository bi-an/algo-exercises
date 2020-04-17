/*
牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。
同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“student. a am I”。
后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a student.”。
Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？
*/

// 思路1：利用string的+操作符
// 先分隔单词，放在vector<string>，然后反向遍历，拼接。

//运行：4ms
class Solution
{
 public:
  string ReverseSentence(string str)
  {
    if (str.empty())
      return str;
    vector<string> sVec;
    size_t pos = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
      if (str[i] == ' ')
      {
        sVec.push_back(str.substr(pos, i - pos));
        pos = i + 1;
      }
    }
    sVec.push_back(str.substr(pos, str.length() - pos));
    string str1;

    for (int i = sVec.size() - 1; i > 0; i--)
    {
      str1 += sVec[i] + ' ';
    }
    str1 += sVec[0];
    return str1;
  }
};

// 思路2：第一次翻转所有字符；第二次逐个翻转单词。

//运行：2ms
class Solution
{
 public:
  string ReverseSentence(string str)
  {
    if (str.empty())
      return str;
    Reverse(&str[0], &str[str.size() - 1]);
    size_t pos = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
      if (str[i] == ' ')
      {
        Reverse(&str[pos], &str[i - 1]);
        pos = i + 1; // 指向下一个单词的开始位置
      }
    }
    Reverse(&str[pos], &str[str.size() - 1]);
    return str;
  }

  void Reverse(char *pBegin, char *pEnd)
  {
    if (pEnd <= pBegin || pBegin == NULL || pEnd == NULL)
      return;
    while (pEnd > pBegin)
    {
      char tmp = *pEnd;
      *pEnd = *pBegin;
      *pBegin = tmp;
      pBegin++;
      pEnd--;
    }
  }
};