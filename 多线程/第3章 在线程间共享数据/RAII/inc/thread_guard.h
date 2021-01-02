#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

// RAII
// 异常安全
// TODO: 但是如果thread结束了，但是thread_guard对象还存在，那不就出问题了吗？
// FIX: 使用移动构造：scoped_thread
class thread_guard
{
  std::thread &t;

 public:
  // explicit防止不安全的隐式转换
  explicit thread_guard(std::thread &t_) : t(t_) {}
  ~thread_guard()
  {
    if (t.joinable())
    {           // 必须检查，因为只允许join一次
      t.join(); // 析构前，等待线程完成；如不想等待，则可以detach
    }
  }
  thread_guard(thread_guard const &) = delete; // 如果该对象被复制，那么可能导致其生存期大于其所绑定的thread，造成thread没有及时被销毁
  thread_guard &operator=(thread_guard const &) = delete;
};

#endif