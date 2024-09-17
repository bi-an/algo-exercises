#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN  // 必须放在包含 doctest.h 之前，生成
                                            // main 函数
#include <bits/stdc++.h>

#include "List.h"
#include "doctest.h"
using namespace std;

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

bool testCore(ListNode *head, ListNode *expect) {
  Solution solution;
  ListNode *ans = solution.mergeNodes(head);
  if (!compareList(ans, expect)) {
    cout << "Answer: ";
    printList(ans);
    cout << "Expect: ";
    printList(expect);
    return false;
  }
  return true;
}

TEST_CASE("test1") {
  ListNode *head = buildList({0, 1, 2, 3, 0});
  ListNode *expect = buildList({6});
  CHECK(testCore(head, expect));
}

TEST_CASE("test2") {
  ListNode *head = buildList({0, 1, 2, 3, 0, 0, 0});
  ListNode *expect = buildList({6});
  CHECK(testCore(head, expect));
}

TEST_CASE("test3") {
  ListNode *head = buildList({0, 1, 2, 3, 0, 0, 0, 4, 0});
  ListNode *expect = buildList({6, 4});
  CHECK(testCore(head, expect));
}

TEST_CASE("test4") {
  ListNode *head = buildList({0, 0});
  ListNode *expect = buildList({});
  CHECK(testCore(head, expect));
}

TEST_CASE("test5") {
  ListNode *head = buildList({0});
  ListNode *expect = buildList({});
  CHECK(testCore(head, expect));
}
