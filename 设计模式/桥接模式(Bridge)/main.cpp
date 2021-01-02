#include "ConcreteImplementor.h"
#include "RefinedAbstraction.h"

int main()
{
  Abstraction *ab = new RefinedAbstraction();

  ab->setImplementor(new ConcreteImplementorA());
  ab->Operation();

  ab->setImplementor(new ConcreteImplementorB());
  ab->Operation();

  return 0;
}