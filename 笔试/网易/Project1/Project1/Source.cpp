#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isTitle(string str, int &start)
{
  if (str[0] == '#')
  {
    int pos = str.find_last_of("#");
    start = pos + 1; // 可能是npos
    return true;
  }
  else
    return false;
}

bool isListItem(string str, int &start)
{
  if (str[0] == '+')
  {
    start = 2; // 不可能是npos
    return true;
  }
  else
    return false;
}

bool isCharacters(string str)
{
  int res = true;
  for (int i = 0; i < str.size(); i++)
  {
    if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z'))
    {
      res = false;
      break;
    }
  }
  return res;
}

bool isNetsite(string str)
{
  bool res = false;
  int pos = str.find("http://", 0);
  if (pos != std::string::npos)
  {
    int pos2 = str.find(".com");
    if (pos2 != std::string::npos && isCharacters(str.substr(pos + 7, pos2 - pos - 7)))
      res = true;
  }
  return res;
}

vector<string> findLink(string &str)
{
  vector<string> res;
  int pos = str.find("](");
  if (pos == std::string::npos)
    return res;

  pos = 0;
  while (pos != std::string::npos)
  {
    int pos1 = str.find("[", pos);
    if (pos1 != std::string::npos)
    {
      int pos2 = str.find("](", pos1 + 1);
      if (pos2 != std::string::npos)
      {
        string tmp = str.substr(pos1 + 1, pos2 - pos1 - 1);
        if (isCharacters(tmp))
        {
          int pos3 = str.find(")", pos2 + 2);
          if (pos3 != std::string::npos)
          {
            if (isNetsite(str.substr(pos2 + 2, pos3 - pos2 - 2)))
            {
              res.push_back(tmp);
              str.erase(pos1, pos3 - pos1 + 1);
              pos = pos3 + 1;
            }
            else
              break;
          }
          else
            break;
        }
        else
        {
          break;
        }
      }
      else
        break;
    }
    else
      break;
  }
  return res;
}

int printNum(string str)
{
  int start = 0;
  int cnt = 0;
  vector<string> links = findLink(str);
  if (isTitle(str, start))
  {
    if (start != std::string::npos)
    {
      //links = findLink(str);
      cnt = str.size() - start;
    }
  }
  else if (isListItem(str, start))
  {
    //links = findLink(str);
    cnt = str.size() - start + 1;
  }
  else
  {
    //links = findLink(str);
    cnt = str.size();
  }

  for (int i = 0; i < links.size(); i++)
  {
    cnt += links[i].size();
  }

  return cnt;
}

int main()
{
  int T; // 测试点数
  cin >> T;
  vector<int> res;
  for (int i = 0; i < T; i++)
  {
    int N; // 行数
    cin >> N;
    char aa = getchar();
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
      string str;
      getline(cin, str);
      cnt += printNum(str);
    }
    res.push_back(cnt);
  }

  for (int i = 0; i < res.size(); i++)
    cout << res[i] << endl;

  return 0;
}