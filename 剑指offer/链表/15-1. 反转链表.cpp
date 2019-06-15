#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	ListNode *next;
	int val;
	ListNode(int _val) :val(_val), next(nullptr) {}
};

// 将从第start个到第end个之间（闭区间）的节点反转过来
void reverseList(ListNode *head, int start, int end) {
	if (head == nullptr || start>end) return;
	ListNode *p = head, *pre=nullptr;
	for(int i=1;i<start && p;i++){
		pre = p;
		p = p->next;
	}
	ListNode *p1 = pre, *p2 = p; // 记录当前的位置
	pre = p; // 开始反转链表
	if(!p) return; // 防止异常
	p = p->next;
	for (int i = start; i < end && p; i++) {
		ListNode *post = p->next;
		p->next = pre;
		pre = p;
		p = post;
	}
	if(p2) // 防止异常
		p2->next = p; // 把链表连接起来
	if(p1) // 防止异常
		p1->next = pre;
}

// 以下为测试代码
ListNode *constructList(const vector<int>& vec) {
	if (vec.empty()) return nullptr;
	ListNode *pHead = new ListNode(vec[0]), *p = pHead;
	for (int i = 1; i < vec.size(); i++) {
		ListNode *pNew = new ListNode(vec[i]);
		p->next = pNew;
		p = p->next;
	}
	return pHead;
}

void printList(ListNode *pHead) {
	if (pHead == nullptr)
		return;
	ListNode *p = pHead;
	while (p) {
		cout << p->val << " ";
		p = p->next;
	}
	cout << endl;
}

int main() {
	ListNode *pHead = constructList(vector<int>({ 1,2,3,4,5,6,7,8 }));
	printList(pHead);
	reverseList(pHead, 2, 5);
	printList(pHead);

	return 0;
}