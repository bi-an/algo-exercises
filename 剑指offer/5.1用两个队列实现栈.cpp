#include <iostream>
#include <queue>

using namespace std;

// push: 每次都放进queue1;
// pop: 如果queue1不为空，则把queue1的size-1个元素全部倒进queue2,将最后一个元素弹出；
//		若queue1为空，则把queue2的size-1个元素全部倒进queue1,将最后一个元素弹出。
// TODO: 这样效率很低，有没有更好的方法？
class Solution
{
 public:
  void push(int x)
  {
    queue1.push(x);
  }
  int pop()
  {
    if (!queue1.empty())
    {
      //int size = queue1.size();
      while (queue1.size() > 1)
      {
        queue2.push(queue1.front());
        queue1.pop();
      }
      int value = queue1.front();
      queue1.pop();
      return value;
    }
    else
    {
      if (queue2.empty())
      {
        cout << "The stack is empty." << endl;
        return -1;
      }
      while (queue2.size() > 1)
      {
        queue1.push(queue2.front());
        queue2.pop();
      }
      int value = queue2.front();
      queue2.pop();
      return value;
    }
  }

 private:
  queue<int> queue1;
  queue<int> queue2;
};

int main()
{
  Solution stack;
  for (int i = 1; i <= 3; i++)
  {
    stack.push(i);
  }
  cout << stack.pop() << endl;
  cout << stack.pop() << endl;
  for (int i = 4; i <= 5; i++)
  {
    stack.push(i);
  }
  cout << stack.pop() << endl;
  cout << stack.pop() << endl;
  cout << stack.pop() << endl;
  cout << stack.pop() << endl;
  cout << stack.pop() << endl;

  return 0;
}