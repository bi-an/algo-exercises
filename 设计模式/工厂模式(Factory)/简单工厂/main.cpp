#include "OperationFactory.h"

int main()
{

  Operation *operAdd = OperationFactory::CreateOperation("+");
  operAdd->numberA = 10;
  operAdd->numberB = 7;

  double result = operAdd->GetResult();

  return 0;
}