#pragma once
#include "../Operation.h"

// 工厂方法

// 工厂接口
class IFactory{
public:
	virtual Operation* CreateOperation()=0;
};

// 产品工厂
class AddFactory : public IFactory{
public:
	Operation* CreateOperation() override{
		return new OperationAdd();
	}
};

class SubFactory: public IFactory{
public:
	Operation* CreateOperation() override{
		return new OperationSub();
	}
};

class MulFactory: public IFactory{
public:
	Operation* CreateOperation() override{
		return new OperationMul();
	}
};

class DivFactory: public IFactory{
public:
	Operation* CreateOperation() override{
		return new OperationDiv();
	}
};