#include "OperationFactory.h"

int main(){

	OperationAdd *operAdd=dynamic_cast<OperationAdd*>(OperationFactory::createOperation("+"));
	operAdd->_numberA = 10;
	operAdd->_numberB = 7;

	double result = operAdd->GetResult();

	return 0;
}