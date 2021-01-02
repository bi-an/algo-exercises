/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/

//方法1：后进先出，用栈实现
class Solution
{
 public:
  vector<int> printListFromTailToHead(ListNode *head)
  {
    vector<int> vec;
    if (head == nullptr)
      return vec;
    stack<int> stk;
    ListNode *p = head;
    while (p != nullptr)
    {
      stk.push(p->val);
      p = p->next;
    }
    while (!stk.empty())
    {
      vec.push_back(stk.top());
      stk.pop();
    }
    return vec;
  }
};

//方法2：递归本身就是一个栈结构
//但是，如果链表很长，则递归很深，可能导致函数调用栈溢出，这样鲁棒性不好。方法1好一些。
class Solution
{
 public:
  vector<int> printListFromTailToHead(ListNode *head)
  {
    vector<int> vec;
    printListFromTailToHead(vec, head);
    return vec;
  }

  void printListFromTailToHead(vector<int> &vec, ListNode *head)
  {
    if (head == nullptr)
      return;
    printListFromTailToHead(vec, head->next);
    vec.push_back(head->val);
  }
};

//写法2
// 1->2->3->4->NULL
// 递归过程：
// f(1)->f(2)->f(3)->f(4)->f(NULL)
// 到达f(NULL)，return vector<int>();
// 回到f(4)，vec.push_back(4)，return;
// ...
// 没有重复计算
// 但是，递归要保存上下文，内存耗费应该要多一些。
class Solution
{
 public:
  vector<int> printListFromTailToHead(ListNode *head)
  {
    vector<int> vec;
    if (head == nullptr)
      return vec;
    vec = (printListFromTailToHead(head->next));
    vec.push_back(head->val);
    return vec;
  }
};

//方法3：利用vector可以在头部插入，或者用反向迭代器
// 分析：vector线性结构，在头部插入效率非常低下。
class Solution
{
 public:
  vector<int> printListFromTailToHead(ListNode *head)
  {
    //stack<int> stack;
    vector<int> vec;
    while (head != NULL)
    {
      vec.insert(vec.begin(), head->val);
      head = head->next;
    }
    return vec;
  }
};

// 测试结果：效率最高
// 分析，vector是数组结构，存取效率比栈高
class Solution
{
 public:
  vector<int> printListFromTailToHead(struct ListNode *head)
  {
    vector<int> v;
    ListNode *p = head;
    while (p != nullptr)
    {
      v.push_back(p->val);
      p = p->next;
    }
    //反向迭代器创建临时对象
    return vector<int>(v.rbegin(), v.rend());
  }
};

/**
 * @brief 两次遍历：
 * 第一次，计算链表长度，确定vector的大小；
 * 第二次，从vector的最右边开始填充
 * 
 */
class Solution
{
 public:
  vector<int> printListFromTailToHead(ListNode *head)
  {
    int n = 0;
    ListNode *p = head;
    while (p != nullptr)
    {
      n++;
      p = p->next;
    }
    vector<int> vec(n);
    p = head;
    while (p != nullptr)
    {
      vec[--n] = p->val;
      p = p->next;
    }
    return vec;
  }
};