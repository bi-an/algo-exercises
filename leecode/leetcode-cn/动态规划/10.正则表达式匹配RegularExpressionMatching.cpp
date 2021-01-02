//由于情况很多，所以用递归实现
class Solution
{
 public:
  bool isMatch(string s, string p)
  {
    if (p.empty())
      return s.empty();
    return isMatchCore(s, p, 0, 0);
  }

  bool isMatchCore(const string &s, const string &p, int p1, int p2)
  {
    int len1 = s.end() - s.begin(), len2 = p.end() - p.begin();
    if (p2 >= len2)
      return (p1 >= len1);
    bool first_match = (p1 < len1) && (s[p1] == p[p2] || p[p2] == '.');

    if (len2 - p2 >= 2 && p[p2 + 1] == '*')
    {
      return (isMatchCore(s, p, p1, p2 + 2) || (first_match && isMatchCore(s, p, p1 + 1, p2)));
    }
    else
    {
      return first_match && isMatchCore(s, p, p1 + 1, p2 + 1);
    }
  }
};