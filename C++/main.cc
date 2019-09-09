#include <stdio.h>
using namespace std;

void foo(unsigned short* ret){
	*ret = 0x4455;
}

int main(){
	unsigned char a = 0x11;
	unsigned char b = 0x22;
	unsigned char c = 0x33;

	foo((unsigned short*)&b);

	// 栈由高地址向低地址（向下）生长，堆向上生长
	// printf("&a=%p\n",&a); // &a=0x7fff01c3359f
	// printf("&b=%p\n",&b); // &b=0x7fff01c3359e
	// printf("&c=%p\n",&c); // &c=0x7fff01c3359d

	// 如果上面三行不注释掉，就变成 44 55 33 了，为什么？
	printf("%x %x %x \n",a,b,c); // 11 55 44

	return 0;
}
