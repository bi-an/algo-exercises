#include "SharedPtr.h"

void fun() {
	SharedPtr<int> sp(new int(10));
	WeakPtr<int> wp(sp);

	int a = 10;
	a++;
}

int main() {
	fun();

	return 0;
}