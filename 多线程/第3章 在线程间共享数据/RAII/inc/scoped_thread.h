#ifndef SCOPED_THREAD_H
#define SCOPED_THREAD_H

#include <exception> // logic_error
#include <thread>

// thread不允许复制构造/赋值，允许移动构造/赋值
class scoped_thread
{
  std::thread thread;

 public:
  explicit scoped_thread(std::thread t_)
      :                // 为什么不用引用传递呢？
      t(std::move(t_)) // 移动构造thread对象，避免了thread_guard以引用方式带来的问题：thread结束，但是thread_guard对象依然存在
  {
    if (!t.joinable())
      throw std::logic_error("No thread");
  }
  ~scoped_thread()
  {
    t.join(); // 析构前等待线程完成
  }
  scoped_thread(const scoped_thread &) = delete;
  scoped_thread &operator=(const scoped_thread &) = delete;
};

#endif
