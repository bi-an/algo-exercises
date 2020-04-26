#include "../inc/func.h"
#include "../inc/thread_guard.h"

void f()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread t(my_func);
  thread_guard g(t); // 把线程立即交给thread_guard管理，异常安全

  do_something_in_current_thread();
}