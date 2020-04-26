#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

std::vector<std::string> split(std::string str, char delimiter = ' ')
{
  std::vector<std::string> res;
  if (str.empty())
    return res;
  str += delimiter; // 小技巧：先在后面加上一个分隔符
  int pos1 = 0;
  while (str[pos1] == delimiter)
    pos1++;
  for (int pos2; pos2 = str.find(delimiter, pos1), pos2 != std::string::npos;)
  {
    std::string tmp = str.substr(pos1, pos2 - pos1);
    res.push_back(tmp);
    pos1 = pos2 + 1;
  }
  return res;
}

bool ipv4(string str)
{
  int pos = str.find(".");
  if (pos == string::npos)
    return false;
  pos = str.find(":");
  if (pos != string::npos)
    return false;
  auto vec = split(str, '.');
  if (vec.size() != 4)
    return false;
  for (int i = 0; i < vec.size(); i++)
  {
    string s = vec[i];
    if (s[0] == '0' && s.size() > 1)
      return false;
  }
  for (int i = 0; i < vec.size(); i++)
  {
    string s = vec[i];
    int a = atoi(s.c_str());
    if (a < 0 || a > 255)
      return false;
  }
  return true;
}

bool ipv6(string str)
{
  int pos = str.find(".");
  if (pos != string::npos)
    return false;
  pos = str.find(":");
  if (pos == string::npos)
    return false;
  auto vec = split(str, ':');
  if (vec.size() != 8)
    return false;
  for (int i = 0; i < vec.size(); i++)
  {
    string s = vec[i];
    if (s.size() > 4)
      return false;
    for (int j = 0; j < s.size(); j++)
    {
      if (s[j] >= '0' && s[j] <= '9' || s[j] >= 'a' && s[j] <= 'f' || s[j] >= 'A' && s[j] <= 'F')
        continue;
      else
        return false;
    }
  }
  return true;
}

int main()
{
  string str;
  cin >> str;
  string ans;
  if (ipv4(str))
    ans = "IPv4";
  else if (ipv6(str))
    ans = "IPv6";
  else
    ans = "Neither";

  cout << ans << endl;

  return 0;
}