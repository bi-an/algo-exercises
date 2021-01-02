// 两个栈，每次push放在stack1,
// 当pop（同时取出值），如果stack2为空，则把stack1的元素全部倒入stack2，（此时就是先进先出的顺序）然后取出；
// 		如果stack2不为空，直接取出stack2的顶端值。

//写法1
class Solution
{
 public:
  void push(int node)
  {
    stack1.push(node);
  }

  int pop()
  {
    if (stack2.empty())
    {
      while (!stack1.empty())
      {
        stack2.push(stack1.top());
        stack1.pop();
      }
    }
    if (stack2.empty())
    {
      //throw new expection("The queue is empty!");
      cout << "The queue is empty!" << endl;
      return -1; //可以用一个全局变量来表明 //但是，抛出异常似乎更好
    }
    int value = stack2.top();
    stack2.pop();
    return value;
  }

 private:
  stack<int> stack1;
  stack<int> stack2;
};

//写法2
class Solution
{
 public:
  void push(int node)
  {
    stack1.push(node);
    if (stack2.empty())
    {
      while (!stack1.empty())
      {
        stack2.push(stack1.top());
        stack1.pop();
      }
    }
  }

  int pop()
  {
    if (stack1.empty() && stack2.empty())
    {
      cout << "The queue is empty!" << endl;
      exit(1);
    }
    if (!stack2.empty())
    {
      int temp = stack2.top();
      stack2.pop();
      return temp;
    }
    else
    {
      while (!stack1.empty())
      {
        stack2.push(stack1.top());
        stack1.pop();
      }
      int temp = stack2.top();
      stack2.pop();
      return temp;
    }
  }

 private:
  stack<int> stack1;
  stack<int> stack2;
};
