#include <stdio.h>
#include <string.h>

static char hello[] = "hillo";
static char world[] = "world";

int main() {
	memcpy(&hello+1, "e", sizeof("e"));
	printf("%s %s\n", hello, world);
}

// 结果：
// VC下： hillo world
// linux下： hillo e

// 解析:
// int arr[10];
// 对数组名取址，得到的是整个数组的地址，也就是说 &arr=arr=&arr[0] ，这跟对指针取址不一样
// 由于得到是整个数组的地址，所以 &arr+1 将会偏移 sizeof(arr) ；
// 但是 arr+1 或 &arr[0]+1 都只偏移一个数组元素的位置，即偏移 sizeof(int)

// VC下，会自动字节的对齐，hello和world的偏移量是8（4的倍数）
// linux下，全局变量没有字节对齐

// sizeof(long)
// 在VC下，x64为4字节，x86为4字节
// 在linux下，x64为8个字节，x86为4字节


// 1, delete this
#include <iostream>
using namespace std;

class S {
public:
	~S() {
		printf("~S");
		delete this; // 段错误，delete this会再次调用析构函数，这样层层调用析构函数，会导致栈溢出
	}
};

void fun() {
	S s;
}

int main() {
	fun();

	return 0;
}



// 2, delete this
#include <iostream>
using namespace std;

class S {
public:
	//~S() {
	//	printf("~S");
	//	delete this; // 段错误，delete this会再次调用析构函数，这样层层调用析构函数，会导致栈溢出
	//}
	void Release() {
		delete this;
	}
};

void fun() {
	S s;
	s.Release();
}

int main() {
	fun(); // 段错误，因为Release已经析构了一次，fun()退出时，s对象消亡，又会调用析构函数，所以会段错误（在错误的内存处释放）

	return 0;
}


// 3, delete this
#include <iostream>
using namespace std;

class S {
public:
	void Release() {
		delete this;
	}
};

int main() {
	S s;
	s.Release(); // 还是会出错，因为不能对对象delete this

	return 0;
}


// 4, delete this
#include <iostream>
using namespace std;

class S {
public:
	void Release() {
		delete this;
	}
	void Fun() {
		cout << "S::Fun()" << endl;
		cout << "S.val=" << val << endl; // 调用Release()之后，val会是随机值
	}

	int val = 10;
};

int main() {
	S *s = new S;
	cout << s->val << endl; // 输出：10
	s->Release(); // 在堆中delete this是可以的
	s->Fun(); // 还能调用成员函数，成员函数需要对象指针this，这是为了访问数据成员，只要成员函数没有调用数据成员，就不会出错。
	cout << s->val << endl; // 不会报错，但是输出结果是随机的
	//s->Release(); // 报错：不能再次delete
	return 0;
}


// 析构与成员对象
#include <iostream>
using namespace std;

class Base {
public:
	Base() {
		cout << "Base()" << endl;
		fun();
	}
	~Base() {
		cout << "~Base()" << endl;
		fun();
		cout << "val=" << val << endl; // 输出正确
	}
	void fun() {
		cout << "Base::fun()" << endl;
	}
	int val = 10;
};

void fun() {
	Base b;
}

int main() {
	fun(); 
	/*
	输出：

	Base::fun()
	~Base()
	Base::fun()
	val=10
	*/
	return 0;
}
// 结论：析构函数只针对数据成员，不针对成员函数，成员函数放在代码区，只是被编译器修饰过函数名
// delete this就是调用析构函数，这样所有的对象成员都会被释放，
// 如果没有在对象中分配动态内存，数据成员的释放是在析构函数中所有代码执行完之后、析构函数退出之前，在析构函数中调用成员对象是正确的
// 这意味着，如果编译器在析构函数中插入了某些释放内存的代码的话（例如析构上面的val），也是在所有用户代码之后插入

// 以下代码也是正确的，因为析构只针对数据成员，调用成员函数可以的，如果fun()中使用了成员数据，那么会是随机值，因为数据成员已经被释放了
int main(){
	Base *pb = new Base;
	delete pb;
	pb->fun();
}