#include <algorithm>
#include <functional>
#include <vector>
using namespace std;

class Solution
{
 public:
  void Insert(int num)
  {
    if (((max.size() + min.size()) & 1) == 0) // 奇数
    {
      if (min.size() > 0 && num > min[0])
      {
        min.push_back(num);
        push_heap(min.begin(), min.end(), greater<int>());
        num = min[0];
        pop_heap(min.begin(), min.end(), greater<int>());
        min.pop_back();
      }
      max.push_back(num);
      push_heap(max.begin(), max.end(), less<int>());
    }
    else // 偶数
    {
      if (max.size() > 0 && num < max[0])
      {
        max.push_back(num);
        push_heap(max.begin(), max.end(), less<int>());
        num = max[0];
        pop_heap(max.begin(), max.end(), less<int>());
        max.pop_back();
      }
      min.push_back(num);
      push_heap(min.begin(), min.end(), greater<int>());
    }
  }

  double GetMedian()
  {
    if (max.size() == 0) //return -1;
      throw exception("Have no numbers.");

    if (((max.size() + min.size()) & 1) == 0)
    { //偶数
      return ((double)max[0] + (double)min[0]) / 2;
    }
    else
    {
      return max[0];
    }
  }

 private:
  vector<int> max; //存放第奇数个节点
  vector<int> min; //存放第偶数个节点
};