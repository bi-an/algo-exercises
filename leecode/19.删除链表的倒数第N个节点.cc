// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head==nullptr) return nullptr;
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        ListNode* fast = dummy, *slow = dummy;
        int i=0;
        for(;i<n+1 && fast!=nullptr;i++)
            fast = fast->next;
        if(i<n+1) return nullptr;
        while(fast){
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* p = slow->next, * post = p->next;
        delete p;
        slow->next = post;
        p = dummy->next;
        delete dummy;
        return p;
    }
};