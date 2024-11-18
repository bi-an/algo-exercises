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

// 没什么技巧，按部就班
class Solution {
public:
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* dummy = new ListNode;
        dummy->next = list1;
        ListNode* p1 = dummy;
        int n = -1;
        while(++n < a){
            p1 = p1->next;
        }
        ListNode* toBeDeleted = p1->next;
        while(n++ <= b) {
            ListNode* next = toBeDeleted->next;
            delete toBeDeleted;
            toBeDeleted = next;
        }
        p1->next = list2;
        ListNode* p = list2;
        while(p->next){
            p = p->next;
        }
        p->next = toBeDeleted;
        
        p = dummy->next;
        delete dummy;
        return p;
    }
};