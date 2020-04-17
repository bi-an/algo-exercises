/*
题目：二维数组，从左至右递增，从上至下递增
*/

class Solution
{
 public:
  bool Find(int target, vector<vector<int>> array)
  {
    for (auto iter1 = array.begin(); iter1 != array.end(); iter1++)
    {
      for (auto iter2 = (*iter1).end() - 1; iter2 != (*iter1).begin() - 1; iter2--)
      {
        int element = (*iter2);
        if (target == element)
        {
          return true;
        }
        if (target < element)
        {
          continue;
        }
        break;
      }
    }
    return false;
  }
};

class Solution
{
 public:
  bool Find(int target, vector<vector<int>> array)
  {
    for (auto iter1 = array.begin(); iter1 != array.end(); iter1++)
    {
      for (auto iter2 = (*iter1).rbegin(); iter2 != (*iter1).rend(); iter2++)
      { //反向迭代器
        int element = (*iter2);
        if (target == element)
        {
          return true;
        }
        if (target < element)
        {
          continue;
        }
        break;
      }
    }
    return false;
  }
};

class Solution
{
 public:
  bool Find(int target, vector<vector<int>> array)
  {
    if (array.empty())
      return false;
    int rows = array.size();
    int cols = array[0].size();
    for (int i = 0; i < rows; i++)
    {
      for (int j = cols - 1; j >= 0; j--)
      { //从右上方开始查找
        if (array[i][j] == target)
          return true;
        if (array[i][j] > target)
        {
          cols--;
        }
      }
    }
    return false;
  }
};

class Solution
{
 public:
  bool Find(int target, vector<vector<int>> array)
  {
    if (array.empty())
      return false;
    int rows = array.size();
    int cols = array[0].size();

    int i = 0, j = cols - 1;
    while (i < rows && j >= 0)
    {
      int temp = array[i][j];
      if (temp == target)
        return true;
      if (temp > target)
      {
        cols--;
        j--;
      }
      else
      {
        i++;
      }
    }
    return false;
  }
};