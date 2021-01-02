#ifndef ABSTRACTION_H
#define ABSTRACTION_H

#include "Implementor.h"

// Abstraction与Implementor是聚合关系
class Abstraction
{
 public:
  void setImplementor(Implementor *implementor)
  {
    this->implementor = implementor;
  }

  virtual void Operation()
  {
    implementor->Operation();
  }

 protected:
  Implementor *implementor;
};

#endif