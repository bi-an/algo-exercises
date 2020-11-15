// 错误，但是能通过牛客测试
// 牛客网的bug:
// 反例 1->2->4->7->8
// 3->5->6
class Solution
{
 public:
  ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
  {
    if (!pHead1)
      return pHead2;
    if (!pHead2)
      return pHead1;

    ListNode *p1 = pHead1, *p2 = pHead2;
    ListNode *p3 = NULL;
    if (p1->val < p2->val)
    {
      pHead1 = p1;
    }
    else
    {
      pHead1 = p2;
    }

    while (p1 && p2)
    {
      if (p1->val < p2->val)
      {
        p3 = p1->next;
        p1->next = p2;
        p1 = p3;
      }
      else
      {
        p3 = p2->next;
        p2->next = p1;
        p2 = p3;
      }
    }

    return pHead1;
  }
};

// 正确
// 推荐写法
class Solution
{
 public:
  ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
  {
    //if (pHead1 == nullptr || pHead2 == nullptr) return nullptr;
    ListNode *p1 = pHead1, *p2 = pHead2;
    ListNode *pNewHead = new ListNode(0), *p = pNewHead; //哨兵

    while (p1 != nullptr && p2 != nullptr)
    {
      if (p1->val < p2->val)
      {
        p->next = p1;
        p1 = p1->next;
      }
      else
      {
        p->next = p2;
        p2 = p2->next;
      }
      p = p->next;
    }
    if (p1 != nullptr)
      p->next = p1;
    if (p2 != nullptr)
      p->next = p2;
    p = pNewHead->next;
    delete pNewHead; //释放哨兵
    return p;
  }
};

//递归

// @Athor zzg
// 正确
class Solution
{
 public:
  ListNode *Merge(ListNode *pHead1, ListNode *pHead2)
  {
    if (pHead1 == nullptr)
      return pHead2;
    if (pHead2 == nullptr)
      return pHead1;

    ListNode *p1 = pHead1, *p2 = pHead2;
    while (p1 != nullptr && p2 != nullptr)
    {
      if (p1->val <= p2->val)
      {
        ListNode *p3 = p1->next;
        if (p3 == nullptr || p3 != nullptr && p3->val > p2->val) // 这一步很重要，牛客网有bug，没有这一步也可以通过
          p1->next = p2;
        p1 = p3;
      }
      else
      {
        ListNode *p3 = p2->next;
        if (p3 == nullptr || p3 != nullptr && p3->val > p2->val)
          p2->next = p1;
        p2 = p3;
      }
    }
    ListNode *res = nullptr;
    if (pHead1->val <= pHead2->val)
      res = pHead1;
    else
      res = pHead2;

    return res;
  }
};