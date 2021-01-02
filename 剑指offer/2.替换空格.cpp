//从右往左找，可以减少移动数组的次数，降低时间复杂度：从O(n^2)到O(n).
class Solution
{
 public:
  void replaceSpace(char *str, int length)
  {
    if (str == nullptr || length <= 0)
      return;

    int cnt_blank = 0;
    int real_len = 0;
    for (int i = 0; i < length && str[i] != '\0'; i++)
    {
      if (str[i] == ' ')
        cnt_blank++;
      real_len++;
    }
    char *p1 = str + real_len;
    int new_len = real_len + cnt_blank * 2;
    char *p2 = str + new_len;

    //边界检查
    if (new_len > length)
      return;

    while (p2 > p1)
    {
      if (*p1 != ' ')
      {
        *p2 = *p1;
        p1--;
        p2--;
      }
      else
      {
        *p2-- = '0'; //因为*和--优先级相同，从左到右，*p2='0'; p2--;
        *p2-- = '2'; //str[i--]='2'; //等价于str[i]='2'; i--;
        *p2-- = '%';
        p1--;
      }
    }
  }
};

/**
 * @author zzg
 */
#include <stdio.h>
#include <string.h>
class Solution
{
 public:
  // length：数组大小，不是字符串长度
  void replaceSpace(char *str, int length)
  {
    if (str == nullptr || length <= 0)
      return;
    int numBlanks = 0, n = strlen(str);
    for (int i = 0; i < n; i++)
    {
      if (str[i] == ' ')
        numBlanks++;
    }
    int i = n - 1, j = n + numBlanks * 2 - 1; // i: read; j: write
    str[j + 1] = '\0';
    while (i >= 0)
    {
      if (str[i] == ' ')
      {
        str[j--] = '0';
        str[j--] = '2';
        str[j--] = '%';
      }
      else
      {
        str[j--] = str[i];
      }
      --i;
    }
  }
};