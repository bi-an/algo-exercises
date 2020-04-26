#include <iostream>
using namespace std;

bool comp(pair<int, int> &it1, pair<int, int> &it2)
{
  return it1.second < it2.second;
}

vector<int> get(const vector<int> &arr)
{
  vector<int> ans;
  if (arr.empty())
    return ans;
  ans.resize(arr.size());
  map<int, int> mymap;
  for (int i = 0; i < arr.size(); i++)
  {
    mymap.insert(make_pair(i, arr[i]));
  }
  sort(mymap.begin(), mymap.end(), comp);
  int p = 0;
  for (auto it = mymap.begin(); it != mymap.end(); it++)
  {
    ans[p] = it->first;
    p++;
  }
  return ans;
}