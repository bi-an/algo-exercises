/*
 * @Author: your name
 * @Date: 2022-03-26 23:31:47
 * @LastEditTime: 2022-03-26 23:35:29
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\2.两数相加.cc
 */

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

// 不好的写法
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = new ListNode();
        ListNode* p = head;
        int carry = 0;
        while (l1 != nullptr && l2 != nullptr) {
            int val = l1->val + l2->val + carry;
            carry = val / 10;
            p->next = new ListNode(val % 10);
            l1 = l1->next;
            l2 = l2->next;
            p = p->next;
        }
        ListNode* l = l1 != nullptr ? l1 : l2;
        while (l != nullptr) {
            int val = l->val + carry;
            carry = val / 10;
            p->next = new ListNode(val % 10);
            l = l->next;
            p = p->next;
        }
        if (carry != 0)
            p->next = new ListNode(carry);
        return head->next;
    }
};

// 更好的写法
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * head = new ListNode();
        ListNode* p = head;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int sum = carry;
            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            p->next = new ListNode(sum % 10);
            carry = sum / 10;
            p = p->next;
        }
        return head->next;
    }
};