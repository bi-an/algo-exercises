/*
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，
序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的）
*/
class Solution
{
 public:
  bool IsPopOrder(vector<int> pushV, vector<int> popV)
  {
    if (pushV.size() == 0 || popV.size() == 0)
      return false;
    stack<int> S;   //辅助栈
    size_t pos = 0; //popV[pos]
    for (size_t i = 0; i < pushV.size(); i++)
    { //对S压栈
      S.push(pushV[i]);
      if (S.top() == popV[pos])
      {
        S.pop();
        pos++;
      }
    }
    while (!S.empty())
    { //S弹栈，同时检查是否与popV顺序一致
      if (S.top() != popV[pos])
        return false;
      S.pop();
      pos++;
    }
    return true;
  }
};

// @Athor zzg
class Solution
{
 public:
  bool IsPopOrder(vector<int> pushV, vector<int> popV)
  {
    if (pushV.size() != popV.size())
      return false;
    if (pushV.empty() && popV.empty())
      return true;

    int i = 0, j = 0;
    while (j < popV.size())
    {
      if (!m_stack.empty() && m_stack.top() == popV[j])
      {
        j++;
        m_stack.pop();
      }
      else if (i < pushV.size())
      {
        m_stack.push(pushV[i]);
        i++;
      }
      else
        return false; //或者break;
    }
    if (i != pushV.size() || j != popV.size())
      return false;
    return true;
  }

 private:
  stack<int> m_stack;
};