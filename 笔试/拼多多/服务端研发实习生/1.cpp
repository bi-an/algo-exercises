/*
1 比较版本号 
 
题目描述 
给定两个版本字符串version1和version2，比较两个版本的大小， 
如果version1 > version2， 则返回1； 
如果version1 < version2， 则返回-1； 
如果version1 = version2， 则返回0。 
version非空，只包含数字和字符 '.' 
 
输入格式 
共2行输入，第一行为version1，第二行为version2。 
 
输出格式 
共1行输出，包含一个整数，表示比较结果。 
 
示例 1 
输入
0.1 
1.1

输出 
-1 
 
示例 2 
输入
1.0.1 
1 

输出
1 
*/

#include <iostream>
#include <string>
using namespace std;

int compare(string version1, string version2)
{
  version1 = version1 + ".";
  version2 = version2 + ".";
  int p1 = 0, p2 = 0;
  int pos1 = version1.find(".", 0);
  int pos2 = version2.find(".", 0);
  int diff = 0;
  while (pos1 != string::npos && pos2 != string::npos)
  {
    string str1 = version1.substr(p1, pos1 - p1);
    string str2 = version2.substr(p2, pos2 - p2);
    int v1 = atoi(str1.c_str());
    int v2 = atoi(str2.c_str());
    diff = v1 - v2;
    if (diff != 0)
      break;
    p1 = pos1 + 1;
    pos1 = version1.find(".", p1);
    p2 = pos2 + 1;
    pos2 = version2.find(".", p2);
  }
  if (diff > 0)
    return 1;
  else if (diff == 0)
    return 0;
  else
    return -1;
}

int main()
{
  string version1, version2;
  cin >> version1 >> version2;
  int res = compare(version1, version2);
  cout << res << endl;

  return 0;
}