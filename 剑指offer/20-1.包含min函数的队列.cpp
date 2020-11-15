// 思路：用list存放min值，
// push时判断list的尾，如果要插入的值val小于或等于尾部，则把尾部替换为val
// pop时判断list的头，如果要删除的queque的头部等于list头，则把list头部删掉

class MinQueue
{
  std::queue<int> m_data;
  std::list<int> m_min;

 public:
  void push(int val)
  {
    if (m_min.empty())
    {
      m_min.push_back(val);
    }
    else if (val <= m_min.back())
    {
      m_min.back() = val;
    }
    else
    {
      m_min.push_back(val);
    }
    m_data.push(val);
  }
  int pop()
  {
    assert(!m_data.empty());
    int val = m_data.front();
    m_data.pop();
    if (val == m_min.front())
      m_min.pop_front();
    return val;
  }
  int min()
  {
    assert(!m_min.empty());
    return m_min.front();
  }
  int size()
  {
    return m_data.size();
  }
  bool empty()
  {
    return m_data.empty();
  }
};