class Solution
{
 public:
  vector<string> Combination(string str) {}

  // 从str中取出m个字符的组合
  void Combination(string str, int m, vector<string> &res)
  {
    if (str.size() == m)
    {
      res.push_back(str);
    }
    else
    {
    }
  }
};