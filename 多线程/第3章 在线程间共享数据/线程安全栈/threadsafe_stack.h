#ifndef THREADSAGE_STACK
#define THREADSAGE_STACK

#include <exception>
#include <memory> // shared_ptr
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
  const char *what() const noexcept;
};

template <typename T>
class threadsafe_stack
{
 private:
  std::stack<T> data;
  mutable std::mutex m; // 为了让const成员函数能够修改(因为const成员函数也要上锁)
 public:
  threadsafe_stack() {}
  threadsafe_stack(const threadsafe_stack &other)
  {
    std::lock_guard<std::mutex> lock(other.m); // 复制other时，other对象不能被操作（例如增删等）
    data = other.data; // 不能在初始化列表中复制，以保证互斥元被整个副本持有(简言之，复制之前必须上锁)
                       // 因为初始化列表不能保证顺序（按照声明顺序），并且lock_guard对象不是成员，不能出现在初始化列表
  }
  threadsafe_stack &operator=(const threadsafe_stack &) = delete; // 不允许使用operator=复制对象，只能复制构造 TODO: 为什么？

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }
  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty())
      throw empty_stack();                                         // 如果栈为空，抛出异常
    std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 构造元素，并且用shared_ptr接管
    data.pop();
    return res;
  }
  void pop(T &value)
  { // 第二种方案：传递引用
    std::lock_guard<std::mutex> lock(m);
    if (data.empty())
      throw empty_stack();
    value = data.top();
    data.pop();
  }
  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};

#endif

// 点评：
// 1. 删掉了top()等接口，使得锁粒度增大。
// 2. 采取了两种方案：shared_ptr和引用传递，避免复制时发生异常。
// 如果锁粒度过大，一个可能导致问题的调用如下：
#if 0
Stack<int> s;
if (!s.empty()) { // (1)
	int const value = s.top(); // (2)
	s.pop(); // (3)
	do_something(value);
}
#endif
// 问题1：(2)对于空栈的调用是未定义行为
// 问题2：(2)(3)之间，可能栈内一个元素被操作两次(do_something)，而另外一个元素没有被操作却被删除了
// 问题3：复制异常，如果T是vector类型，return一个值可能导致bad_alloc异常
