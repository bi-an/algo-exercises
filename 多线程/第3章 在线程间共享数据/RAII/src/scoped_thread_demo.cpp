#include "../func.h"
#include "../inc/scoped_thread.h"

void f()
{
  int some_local_state;
  scoped_thread t(std::thread(func(some_local_state)));
  do_something_in_current_thread();
}