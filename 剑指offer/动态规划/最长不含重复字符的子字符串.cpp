// 动态规划
// 计f(i)为第i个字符结尾的最长子字符串长度
// 从0位置向后扫描，若当前字符之前没有出现过，则f(i)=f(i-1)+1
// 若当前字符之前出现过： 计算这个字符距离上一次出现的距离：d
// (1)d<=f(i-1)，则这个字符在f(i-1)的子字符串中，因为f(i-1)的子字符串没有重复字符，
// 所以从这个字符上一次出现之后开始计算，到达当前位置为止，没有重复字符的长度为d，所以f(i)=d;
// (2)d>f(i-1)，则这个字符超出了f(i-1)的子字符串，所以从上一次开始计算的子字符串,一直到第i个字符(包括)，
// 没有重复的字符，所以f(i)=f(i-1)+1.

// @Athor zzg
int longestSubstringWithoutDuplication(const string &str)
{
  if (str.empty())
    return 0;
  int position[26];
  for (int i = 0; i < 26; i++)
    position[i] = -1;

  int curLen = 0, maxLen = 0;
  for (int i = 0; i < str.length(); i++)
  {
    char ch = str[i];
    int pos = ch - 'a';
    if (position[pos] < 0)
    { //没有出现过
      position[pos] = i;
      curLen++;
    }
    else
    { //这个字符之前出现过
      int d = i - position[pos];
      if (d <= curLen)
      {
        curLen = d;
      }
      else
      {
        curLen++;
      }
      //lastLen=curLen;
      position[pos] = i; //记录本次的位置
    }
    if (curLen > maxLen)
      maxLen = curLen;
  }

  if (curLen > maxLen)
    maxLen = curLen;

  return maxLen;
}