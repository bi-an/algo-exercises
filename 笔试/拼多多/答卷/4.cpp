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