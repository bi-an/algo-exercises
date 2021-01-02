class Solution
{
 public:
  bool isNumeric(char *string)
  {
    if (string == nullptr)
      return false;
    bool res = scanInteger(&string);
    if (*string == '.')
    {
      string++;
      //"3."和".3"认为合法，所以用||
      //如"3.14e6",扫描到"."之后，还需要往后扫描"14"，所以scanInteger必须放在||前面
      //总结：对于||，左边和右边元素位置关系要慎重考虑
      res = scanInteger(&string) || res;
    }
    if (*string == 'e' || *string == 'E')
    {
      string++;
      //"3e"和"e6"都认为不合法，所以用&&
      res = res && scanInteger(&string);
    }
    return res && *string == '\0';
  }

  bool scanInteger(char **str)
  {
    if ((*str)[0] == '+' || (*str)[0] == '-') //[]优先级高于*
      ++*str;
    return scanUnsignedInteger(str);
  }

  bool scanUnsignedInteger(char **str)
  {
    const char *before = *str;
    while (**str != '\0' && **str >= '0' && **str <= '9')
      (*str)++; //*与++优先级相同,结合顺序右到左
    //当字符串中含有若干数字，则返回true
    return *str > before;
  }
};