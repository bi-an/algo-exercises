class Solution
{
 public:
  int strStr(string haystack, string needle)
  {
    if (needle == "")
      return 0;

    vector<int> next(needle.length());
    fillNext(needle, next);
    int i = 0, j = 0;
    while (i < haystack.length())
    {
      if (haystack[i] != needle[j])
      {
        // 失配
        if (j == 0)
          ++i;
        else
          j = next[j];
      }
      else
      {
        // 匹配
        ++i;
        ++j;
      }
      if (j == needle.length())
      {
        return i - needle.length();
      }
    }
    return -1;
  }

  void fillNext(string &pattern, vector<int> &next)
  {
    // 如果 pattern 字符个数少于 2 个，则 next 不会被访问，可以不填充
    if (pattern.length() < 2)
        return;
    assert(pattern.length() == next.size());

    next[0] = -1;
    next[1] = 0;
    int pos = 2, cnd = next[1];
    while (pos < pattern.length())
    {
      if (pattern[pos - 1] == pattern[cnd])
      {
        cnd = cnd + 1;
        next[pos] = cnd;
        pos = pos + 1;
      }
      else if (cnd > 0)
      {
        cnd = next[cnd];
      }
      else
      {
        next[pos] = 0; // 此时 cnd = 0
        pos = pos + 1;
      }
    }
  }
};