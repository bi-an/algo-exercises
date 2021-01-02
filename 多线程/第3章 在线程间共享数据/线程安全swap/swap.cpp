#include <mutex>

class some_big_object
{
};
void Swap(some_big_object &lhs, some_big_object &rhs);

class X
{
  some_big_object some_detail;
  std::mutex m;

 public:
  X(some_big_object const &sd) : some_detail(sd) {}

  friend void Swap(X &lhs, X &rhs)
  {                   // 把友元定义在类内，但是使用Swap(X&, X&)前需要先声明
    if (&lhs == &rhs) // 确保不是自我交换，因为在已经上锁的互斥元上再次获取锁是未定义的行为
      return;
    std::lock(lhs.m, rhs.m);                                    // 同时锁定lhs和rhs的互斥元
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 第二个参数告知lock_guard，这个互斥元已经被锁定，不要在构造函数中去锁定它
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    Swap(lhs.some_detail, rhs.some_detail);
  }
};