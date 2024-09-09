/*
 * @lc app=leetcode.cn id=2181 lang=cpp
 *
 * [2181] 合并零之间的节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode *mergeNodes(ListNode *head) {
    ListNode *dummy = new ListNode;
    dummy->next = head;
    ListNode *start = head, *prev = dummy;
    while (start) {
      // 删除中间节点
      ListNode *p = start->next;
      while (p && p->val != 0) {
        ListNode *next = p->next;
        start->val += p->val;
        delete p;
        p = next;
      }
      // 处理完中间节点之后，start->val还是等于0，
      // 说明没有中间节点
      // 此时p可能为0，也可能为NULL
      if (start->val == 0) {
        prev->next = p;
        delete start;
      } else {
        start->next = p;
        prev = start;
      }
      start = p;
    }
    if (head->val == 0) {
      delete head;
      return nullptr;
    }
    return dummy->next;
  }
};
// @lc code=end

