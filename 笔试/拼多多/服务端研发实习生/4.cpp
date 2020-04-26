/*
4 小熊与狼 
 
题目描述 
N 匹狼要给小熊利马一次考验。每匹狼选择一个大于等于 0 小于等于 2^30-1 的数字，
并向其他所有狼展示这个数字。没有狼会直接把自己的数字告诉利马。有的狼会完全
保持沉默，有的会给利马一些信息。一匹狼会告诉利马的唯一信息是其它所有狼的数
字进行位运算 xor 后的结果。 
利马的目标是找出所有狼选出数字的总和，如果有多种可能，找出最小的那个。 
给出长度为 N 的 int 数组 x，x[i]表示第 i 匹狼提供的信息，没有给出信息用-1 表示。
求最小的可能值之和，如果不存在这种可能，输出-1。 
 
输入格式 
第一行是一个长度为 N 的数字数组 x 
2 <= N <= 40, -1 <= x[i] <= 2^30 - 1 
 
输出格式 
输出一个数字表示最小和。若不可能则输出-1。 
 
示例 1 
输入
{1, 4, 13, -1} 

输出
21 
 
示例 2 
输入
{0,0,7} 

输出
-1 
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int minSum(vector<int> vec)
{
  if (vec.empty())
    return -1;
  std::sort(vec.begin(), vec.end(), std::greater<int>());
  if (vec[0] == -1)
    return -1;
  int Xor = vec[0];
  int sum = vec.size() - 1;
  for (int i = 1; i < vec.size() && vec[i] != -1; i++)
  {
    sum += vec.size() - 1;
    Xor ^= vec[i];
  }
  if (vec[vec.size() - 1] != -1 && sum % 2 == 0 && Xor != 0)
    return -1;
  return -1; // todo
}

int main()
{
  vector<int> vec;
  string str;
  getline(cin, str);
  str = str.substr(1, str.size() - 2);
  int pos1 = 0, pos2 = str.find(",", pos1);
  for (; pos2 != string::npos;)
  {
    int temp = atoi(str.substr(pos1, pos2 - pos1).c_str());
    vec.push_back(temp);
    pos1 = pos2 + 1;
    pos2 = str.find(",", pos1);
  }
  int temp = atoi(str.substr(pos1, pos2 - pos1).c_str());
  vec.push_back(temp);

  cout << minSum(vec) << endl;

  return 0;
}