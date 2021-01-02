#pragma once
#include "Operation.h"
#include <string>

// 简单工厂
class OperationFactory
{
 public:
  OperationFactory() {}

  static Operation *CreateOperation(std::string operate)
  {
    Operation *oper = nullptr;
    if (operate == "+")
      oper = new OperationAdd; // 这好像是依赖，不是关联
    else if (operate == "-")
      oper = new OperationSub;
    else if (operate == "*")
      oper = new OperationMul;
    else if (operate == "/")
      oper = new OperationDiv;
    else
      ;
    return oper;
  }
};