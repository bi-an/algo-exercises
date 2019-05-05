#pragma once
#include <exception>

class Operation{
public:
	Operation(){}
	virtual double GetResult(){
		double result=0;
		return result;
	}

	double numberA=0;
	double numberB=0;
};

class OperationAdd : public Operation{
public:
	double GetResult() override{
		double result=0;
		result=numberA+numberB;
		return result;
	}
};

class OperationSub: public Operation{
public:
	double GetResult() override{
		double result=0;
		result=numberA - numberB;
		return result;
	}
};

class OperationMul:public Operation{
public:
	double GetResult() override{
		double result=0;
		result=numberA*numberB;
		return result;
	}
};

class OperationDiv : public Operation{
public:
	double GetResult() override{
		double result=0;
		if(numberB==0)
			throw std::exception("The divisor cannot be 0.");
		result=numberA/numberB;
		return result;
	}
};