#pragma once
#include <string>
#include "Operation.h"

class OperationFactory{
public:
	OperationFactory(){}

	static Operation* createOperation(std::string operate){
		Operation *oper=nullptr;
		if (operate == "+")
			oper = new OperationAdd;
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