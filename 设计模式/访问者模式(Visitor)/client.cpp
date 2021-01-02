#include "Person.h"

int main()
{
  ObjectStructure o;

  Man man;
  o.Attach(&man);
  o.Attach(&man);      // man被添加了两次
  o.Attach(new Woman); // 这种方式会导致内存泄露，不推荐

  Success v1;
  o.Display(&v1);

  return 0;
}