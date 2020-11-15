//保存前后节点
class Solution
{
 public:
  ListNode *ReverseList(ListNode *pHead)
  {
    if (pHead == nullptr)
      return nullptr;
    ListNode *p = pHead, *pre = nullptr;
    while (p)
    {
      ListNode *next = p->next;
      p->next = pre;
      pre = p;
      p = next;
    }
    return pre;
  }
};