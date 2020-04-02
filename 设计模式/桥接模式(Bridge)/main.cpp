#include "RefinedAbstraction.h"
#include "ConcreteImplementor.h"

int main(){
	Abstraction* ab = new RefinedAbstraction();

	ab->setImplementor(new ConcreteImplementorA());
	ab->Operation();

	ab->setImplementor(new ConcreteImplementorB());
	ab->Operation();

	return 0;
}