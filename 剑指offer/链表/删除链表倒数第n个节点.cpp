#include <iostream>
using namespace std;

struct Node {
	int val;
	Node *next;
	Node(int val_) :val(val_), next(nullptr) {

	}
};

// 如果是删除倒数第1个节点，那么first要先走1步，当first到达null时，last则指向倒数第一个，类推
// 注意：delete之前要把链表连接起来
// 可以用链表1->2->3作为例子来思考：
// 1. 删除中间节点2，first到达null，last指向要删除的2，pre指向1，则pre->next = last->next即可连接起来；
// 2. 删除尾节点3，first到达null，last指向要删除的3，pre指向2，则pre->next = last->next；
// 3. 删除头节点1，first到达null，last指向1，pre==nullptr（初始化为nullptr，可以作为判断是否是要删除头节点的标识），
//	  此时，把root指向last->next即可。
// 由于last一定不为null，所以last->next一定存在。
bool deleteNth(Node** root, int n) {
	if (root == nullptr || n <= 0) return false;
	Node *p = *root;
	int diff = 0;
	while (p != nullptr && diff < n) {
		diff++;
		p = p->next;
	}
	if (diff < n) // 不可以用p==nullptr作为判断条件，例如n个节点链表，要删除倒数第n个，则diff==n, p==nullptr，即while的两个条件可能同时满足
		return false;
	Node *p1 = *root, *pre = nullptr;
	while (p != nullptr) {
		pre = p1;
		p = p->next;
		p1 = p1->next;
	}
	if (pre == nullptr) {
		*root = p1->next;
	}
	else {
		pre->next = p1->next; // 仅仅delete是不够的，还要把链表连接起来
	}
	delete p1;
	return true;
}

int main() {
	Node *p = new Node(1);
	p->next = new Node(2);
	p->next->next = new Node(3);

	// 分别删除倒数第0，1，2，3，4个节点，测试正确
	bool flag = deleteNth(&p, 2);

	// 如果只有一个节点
	Node *p2 = new Node(1);
	bool flag2 = deleteNth(&p2, 1);

	return 0;
}