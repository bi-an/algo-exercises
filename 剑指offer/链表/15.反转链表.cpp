/*
 * @Author: your name
 * @Date: 2020-04-26 20:30:38
 * @LastEditTime: 2021-07-25 00:23:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\剑指offer\链表\15.反转链表.cpp
 * https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/
 */
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

// 递归写法一
// 这其实是循环法的翻版
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return reverse(head, nullptr);
    }

    // 很明显，我们必须获得pre指针，那么可以直接把这个pre作为已知参数输入
    ListNode* reverse(ListNode* head, ListNode* pre) {
        if(!head) return pre;
        ListNode* next = head->next;
        head->next = pre;
        return reverse(next, head);
    }
};

// 递归写法二
// 递归函数f的定义：返回反转后的链表。如图：
//       1 → 2 → 3 → 4 → NULL
//       ↑
//      head
// 当head=1, f(head->next)为
//               1 -- head
//               ↓
//       4 → 3 → 2 → NULL
//       |
//      newHead
// 你会发现此时head依然指向2，此时只要将2改指向1既可：
//               1 -- head
//               ↓↑
//       4 → 3 → 2   NULL
//       |
//      newHead
// 没错，此时会出现一个环，所以还要将head改指为NULL.
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return nullptr;
        // 第二个递归返回条件必不可少，这样才能将最后一个节点作为新的头节点层层返回
        // 否则，递归层层返回的是一个NULL
        if(!head->next) return head; // 以上两步可以合成一步
        ListNode* newHead = reverseList(head->next);
        if(head->next) {
            head->next->next = head;
            head->next = nullptr;
        }
        return newHead;
    }
};