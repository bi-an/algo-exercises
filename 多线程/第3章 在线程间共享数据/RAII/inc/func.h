#ifndef FUNC_H
#define FUNC_H

#include <iostream>

static void do_something(int i)
{
  std::cout << i << " " << endl;
}

struct func
{
  int &i;
  func(int &i_) : i(i_) {}

  void operator()()
  {
    for (int j = 0; j < 100000; j++)
    {
      do_something(i);
    }
  }
};

static do_something_in_current_thread()
{
  cout << "do_something_in_current_thread" << endl;
}

#endif