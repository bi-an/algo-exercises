// 题目：
// 由大写字母组成的字符串，如果有连续4个及4个以上的字母，就用"-"连起来表示，
// 例如"ABCEFGHIJXYZ"将转化成"ABCE-FXYZ"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encode(string str)
{
  if (str.size() <= 3)
    return str;
  string res;
  char first = str[0], last = str[0];
  int cnt = 1;
  for (int i = 1; i <= str.size(); i++)
  {
    if (str[i] - first == cnt)
    {
      cnt++;
      last = str[i];
    }
    else
    {
      if (cnt > 3)
      {
        res += first;
        res += "-";
        res += last;
      }
      else
      {
        for (int j = 0; j < cnt; j++)
        {
          res += (first + j);
        }
      }
      first = str[i];
      last = first;
      cnt = 1;
    }
  }
  return res;
}

int main()
{
  vector<string> input;
  int N;
  cin >> N;
  getchar();
  for (int i = 0; i < N; i++)
  {
    string temp;
    getline(cin, temp);
    input.push_back(temp);
  }
  for (int i = 0; i < N; i++)
  {
    cout << encode(input[i]) << endl;
  }

  return 0;
}