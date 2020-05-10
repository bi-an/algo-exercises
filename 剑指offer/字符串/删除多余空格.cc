/**
 * 删除多余空格
 * 如果有标点符号，删除标点之前的空格
 */

#include <iostream>
using namespace std;

void removeSpaces(string &str)
{
  int n = str.length();
  int i = 0, j = -1; // i写指针，j读指针
  bool spaceFound = false;
  // j定位到第一个非空字符
  while (++j < n && str[j] == ' ')
  {
  }
  // 标点符号列表
  string punctuation_marks = ",.?!";
  while (j < n)
  {
    if (str[j] != ' ')
    {
      // 如果读到标点符号，删除前面写入的空格
      if (punctuation_marks.find_first_of(str[j]) != std::string::npos && i - 1 >= 0 && str[i - 1] == ' ')
      {
        // swap的好处是不增加新的符号，不然很难判断尾部的空格
        swap(str[i - 1], str[j++]); // 这是删除，所以写指针不动
      }
      else
      {
        swap(str[i++], str[j++]);
      }
      spaceFound = false;
    }
    else
    {
      // 如果上一次没有空格，那么写入一个空格
      if (!spaceFound)
      {
        swap(str[i++], str[j]);
        // str[i++] = ' ';
        spaceFound = true;
      }
      // 如果本次和上次读到的都是空格，那么写指针不动，读指针后移
      ++j;
    }
  }
  // 删除尾部的空格
  i = n - 1;
  while (i < n && str[i] == ' ')
    --i;
  str.erase(str.begin() + i + 1, str.end());
}

/// 测试
void test(int id, string in, string out)
{
  cout << id << ":";
  removeSpaces(in);
  if (in == out)
  {
    cout << "right" << endl;
  }
  else
  {
    cout << "false" << endl;
  }
}

int main()
{
  test(1, "I", "I");
  test(2, "I ", "I");
  test(3, " I", "I");
  test(4, " I ", "I");
  test(5, "I am", "I am");
  test(6, " I am", "I am");
  test(7, "I am ", "I am");
  test(8, "  I am  ", "I am");
  test(9, "   ", "");
  test(10, "", "");
  test(11, ".", ".");
  test(12, "  .  ", ".");
  test(13, ".  ", ".");
  test(14, "  .", ".");

  return 0;
}