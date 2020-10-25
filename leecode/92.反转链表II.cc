#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(head==nullptr) return nullptr;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* saved = dummy;
        int i=0;
        // saved指向要反转区间的前一个节点
        for(;i<m-1 && saved;i++){
            saved = saved->next;
        }
        i=m;
        ListNode* p = saved->next;
        for(;i<n;i++){
            // “删掉”p节点的下一个节点
            // 然后把删掉的节点接到saved后面
            // 举例发现：p节点一直不需要改变 TODO
            ListNode* del = p->next;
            p->next = del->next;
            del->next = saved->next;
            saved->next = del;
        }
        return dummy->next;
    }
};