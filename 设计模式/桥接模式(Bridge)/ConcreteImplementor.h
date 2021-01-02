#ifndef CONCRETE_IMPLEMENTOR_H
#define CONCRETE_IMPLEMENTOR_H

#include "Implementor.h"

// 具体实现A
class ConcreteImplementorA : public Implementor
{
 public:
  void Operation() override
  {
    std::cout << "ConcreteImplementorA" << std::endl;
  }
};

// 具体实现B
class ConcreteImplementorB : public Implementor
{
 public:
  void Operation() override
  {
    std::cout << "ConcreteImplementorB" << std::endl;
  }
};

#endif