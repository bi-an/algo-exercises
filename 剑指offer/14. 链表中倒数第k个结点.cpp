/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/

// 链表的尾结点记作倒数第一个节点

//一次遍历链表
class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		if (pListHead == nullptr) return nullptr;

		ListNode *p1 = pListHead, *p2 = pListHead;
		int i = 0;
		for (; i < k && p2 != nullptr; i++) {
			p2 = p2->next;
		}
		if (i < k) return nullptr;
		while (p2 != nullptr) { // 最终p2到达nullptr
			p1 = p1->next;
			p2 = p2->next;
		}
		return p1;
	}
};



//二次遍历链表
class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		if (!pListHead || !k)
			return NULL;
		int length = 1;
		ListNode* p = pListHead->next;
		while (p) {
			length++;
			p = p->next;
		}
		if (k > length) {
			return NULL;
		}
		p = pListHead;
		for (size_t i = 0; i < length - k; i++) {
			p = p->next;
		}
		return p;
	}
};


//相关题目：求链表的中间节点（当链表节点是偶数个时，返回任意一个节点。）
//思路：两个指针，p1一次走1步，p2一次走两步，当p2到链表尾时，p1恰好走到中间。

// 当节点数为偶数时，返回中间的后一个
ListNode *FindMid(ListNode *pListHead) {
	if (pListHead == nullptr) return nullptr;
	ListNode *p1 = pListHead, *p2 = pListHead;
	while (p2 != nullptr && p2->next!=nullptr) {
		p1 = p1->next;
		p2 = p2->next->next;
	}
	return p1;
}

// 当节点数为偶数时，返回中间的前一个
ListNode *FindMid(ListNode *pListHead) {
	if (pListHead == nullptr) return nullptr;
	ListNode *p1 = pListHead, *p2 = pListHead;
	while (p2 != nullptr) {
		p2 = p2->next;
		if (p2 != nullptr && p2->next!=nullptr) {
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return p1;
}