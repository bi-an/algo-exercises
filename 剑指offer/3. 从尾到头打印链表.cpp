/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/

//方法1：后进先出，用栈实现
class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> vec;
		if (head == nullptr) return vec;
		stack<int> stk;
		ListNode *p = head;
		while (p != nullptr) {
			stk.push(p->val);
			p = p->next;
		}
		while (!stk.empty()) {
			vec.push_back(stk.top());
			stk.pop();
		}
		return vec;
	}
};


//方法2：递归本身就是一个栈结构
//但是，如果链表很长，则递归很深，可能导致函数调用栈溢出，这样鲁棒性不好。方法1好一些。
class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> vec;
		printListFromTailToHead(vec, head);
		return vec;
	}

	void printListFromTailToHead(vector<int> &vec, ListNode *head) {
		if (head == nullptr) return;
		printListFromTailToHead(vec, head->next);
		vec.push_back(head->val);
	}
};

//写法2
class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		vector<int> vec;
		if (head == nullptr) return vec;
		vec = (printListFromTailToHead(head->next));
		vec.push_back(head->val);
		return vec;
	}
};

//方法3：利用vector可以在头部插入，或者用反向迭代器
// 分析：vector线性结构，在头部插入效率非常低下。
class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		//stack<int> stack;
		vector<int> vec;
		while (head!=NULL) {
			vec.insert(vec.begin(),head->val);
			head = head->next;
		}
		return vec;
	}
};

// 测试结果：效率最高
// 分析，vector是数组结构，存取效率比栈高
class Solution {
public:
	vector<int> printListFromTailToHead(struct ListNode* head) {
        vector<int> v;
        ListNode *p = head;
        while (p != nullptr) {
           v.push_back(p->val);
           p = p->next;
        }
        //反向迭代器创建临时对象
        return vector<int>(v.rbegin(), v.rend());
    }
};