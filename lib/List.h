#ifndef LIST_H

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* buildList(std::initializer_list<int> ilist) {
    ListNode* dummy = new ListNode;
    ListNode* p = dummy;
    for (int value : ilist) {
        p->next = new ListNode(value);
        p = p->next;
    }
    ListNode* head = dummy->next;
    delete dummy;
    return head;
}

bool compareList(ListNode* head1, ListNode* head2) {
    while (head1 && head2) {
        if (head1->val != head1->val)
            return false;
        else {
            head1 = head1->next;
            head2 = head2->next;
        }
    }
    return head1 == head2; // nullptr
}

void printList(ListNode* head) {
    if (head == nullptr)
        cout << "NULL";
    while (head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

#endif // LIST_H