#include "IFactory.h"

int main()
{
  IFactory *operFactory = new AddFactory();
  Operation *operAdd = operFactory->CreateOperation();
  operAdd->numberA = 10;
  operAdd->numberB = 7;

  double result = operAdd->GetResult();

  return 0;
}