//解法1：利用char数组存放大数

#include <iostream>
using namespace std;

bool Increment(char* number) {
	if (number == nullptr) return false;
	int carry = 0;
	int len = strlen(number);//效率比较低，还不如直接把len传进来，毕竟len都是一样的。
	//int n = 0;
	for (int i = len - 1; i >= 0; i--) {
		int n = number[i] - '0' + carry;
		if (i == len - 1) n++;
		if (n >= 10) {
			if (i == 0) {//O(1)时间效率判断是否达到最大数; 如果直接使用strcmp(number,"99999...99")，则时间效率为O(n)
				return false;
			}
			n -= 10;
			carry = 1;
			number[i]=n+'0';
		}
		else {
			//carry = 0;
			number[i]=n+'0';
			break;//没有进位，就可以结束循环
		}
		//number[i] = n + '0';
	}
	return true;
}

void PrintNumber(char *number) {
	if (number == nullptr) return;
	int len = strlen(number);
	int i = 0;
	for (; i < len; i++)
		if (number[i] != '0')
			break;
	printf("%s ", number + i);
}

//n位数
void Print1ToMaxOfNDigits(int n) {
	if (n <= 0) return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	while (Increment(number)) {
		PrintNumber(number);
	}
	delete[] number;
}

int main() {
	Print1ToMax(3);
	return 0;
}


//解法2：打印从1到最大的n位数，其实就是n个从0到9的全排列。可以递归实现。
//列出0-9的全排列，然后设置下一位，递归结束条件：设置了最后一位。
#include <iostream>
using namespace std;

void PrintNumber(char *number) {
	if (number == nullptr) return;
	int len = strlen(number);
	int i = 0;
	for (; i < len; i++)
		if (number[i] != '0')
			break;
	printf("%s ", number + i);
}

void Print1ToMaxOfNDigits_Recursively(char *number, int length, int index) {
	if (index == length - 1) {
		PrintNumber(number);
		return;
	}

	for (int i = 0; i < 10; i++) {
		number[index + 1] = i + '0';
		Print1ToMaxOfNDigits_Recursively(number, length, index + 1);
	}
}

void Print1ToMaxOfNDigits(int n) {
	if (n <= 0) return;

	char *number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';

	for (int i = 0; i < 10; i++) {
		number[0] = i + '0';
		Print1ToMaxOfNDigits_Recursively(number, n, 0);
	}

	//Print1ToMaxOfNDigits_Recursively(number, n, -1);

	delete[] number;
}

int main() {
	Print1ToMaxOfNDigits(4);
	return 0;
}