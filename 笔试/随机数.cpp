#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int rand6() {
	return rand() % 6 + 1;
}

// 用rand6()产生rand10()
int rand10() {
	int i = 0;
	do {
		i = 6 * (rand6() - 1) + rand6();
	} while (i > 30);
	return i % 10 + 1;
}


// 测试结果表明：概率均等

int main() {
	srand(time(0));

	int times[10] = {};

	for (int i = 9000000; i >= 0; i--) {
		times[rand10()-1]++;
	}

	for (int i = 0; i < 10; i++) {
		cout << times[i] << endl;
	}


	return 0;
}
