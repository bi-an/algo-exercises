#include "SharedPtr.h"

void fun()
{
  SharedPtr<int> sp(new int(10));
  WeakPtr<int> wp(sp);
  if (SharedPtr<int> p = wp.lock())
  {
    int b = 10;
    b++;
  }

  int a = 10;
  a++;
}

int main()
{
  fun();

  return 0;
}