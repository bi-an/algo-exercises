//排序的链表，删除其重复的节点

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution
{
 public:
  ListNode *deleteDuplication(ListNode *pHead)
  {
    if (pHead == nullptr)
      return nullptr;
    ListNode *pPre = nullptr, *pNode = pHead;
    ListNode *pNewHead = pHead;
    while (pNode)
    {
      ListNode *pNext = pNode->next;
      if (pNext && pNext->val == pNode->val)
      {
        int value = pNode->val;
        while (pNode && pNode->val == value)
        {
          pNext = pNode->next;
          delete pNode;
          pNode = pNext;
        }
        if (pPre == nullptr)
        { // 第一次
          pNewHead = pNode;
        }
        else
        {
          pPre->next = pNode;
        }
        if (pNode == nullptr)
        {
          break;
        }
      }
      else
      {
        pPre = pNode;
        pNode = pNext;
      }
    }
    return pNewHead;
  }
};

// @Athor zzg
class Solution
{
 public:
  ListNode *deleteDuplication(ListNode *pHead)
  {
    if (pHead == nullptr)
      return nullptr;
    ListNode *pNewHead = new ListNode(-1); // 哨兵
    pNewHead->next = pHead;
    ListNode *p = pHead, *pre = pNewHead;
    while (p)
    {
      ListNode *post = p->next;
      int value = p->val;
      if (post && post->val == p->val)
      {
        while (p && p->val == value)
        {
          post = p->next;
          delete p;
          p = post;
        }
        pre->next = post;
        continue;
      }
      pre = p;
      p = p->next;
    }
    p = pNewHead->next;
    delete pNewHead; // 删除哨兵
    return p;
  }
};

// @Athor zzg
class Solution
{
 public:
  ListNode *deleteDuplication(ListNode *pHead)
  {
    ListNode *sentry = new ListNode(0); // 哨兵
    sentry->next = pHead;
    ListNode *pre = sentry, *p = pHead;
    while (p)
    {
      if (!p->next)
        break;
      if (p->next->val != p->val)
      {
        pre = p;
        p = p->next;
      }
      else
      {
        int value = p->val;
        while (p && value == p->val)
        {
          ListNode *post = p->next;
          delete p;
          p = post;
        }
        pre->next = p;
      }
    }
    ListNode *res = sentry->next;
    delete sentry;
    return res;
  }
};