#ifndef IMPLEMENTOR_H
#define IMPLEMENTOR_H

#include <iostream>

// “实现”的抽象类
class Implementor
{
 public:
  virtual void Operation() = 0;
};

#endif