/*
求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
*/

//1. 构造函数
class Temp{
public:
	Temp(){
		++N; Sum+=N;
	}

	static int Reset(){
		N=0; Sum=0;
	}

	static int GetSum(){
		return Sum;
	}

private:
	static int N;
	static int Sum;
};
/*
编译错误:您提交的代码无法完成编译
/tmp/a-f8add1.o: In function `main':
a.cc:(.text+0x4844): undefined reference to `Temp::N'
a.cc:(.text+0x484e): undefined reference to `Temp::Sum'
a.cc:(.text+0x4885): undefined reference to `Temp::N'
a.cc:(.text+0x488b): undefined reference to `Temp::Sum'
clang++: error: linker command failed with exit code 1 (use -v to see invocation)
*/
class Solution {
public:
    int Sum_Solution(int n) {
        Temp::Reset();
        Temp *p=new Temp[n];
        delete[] p;
        p=NULL;
        return Temp::GetSum();
    }
};

//测试，在全局域，没有问题
class Temp {
public:
	Temp() { ++N; Sum += N;	}

	static void Reset() {
		N = 0; Sum = 0;
	}
	static int GetSum() {
		return Sum;
	}

private:
	static int N;
	static int Sum;
};

int Temp::N = 0; //静态成员变量定义, 必须在全局域定义
int Temp::Sum = 0;

int Sum_Solution(int n) {
	Temp::Reset();
	Temp* a = new Temp[n];
	delete[] a;
	a = NULL;
	return Temp::GetSum();
}

int main(){
	cout<< Sum_Solution(10);//test
	return 0;
}

//第二次提交，成功
class Temp {
public:
	Temp() { ++N; Sum += N;	}

	static void Reset() {
		N = 0; Sum = 0;//静态成员函数，只能对静态成员变量操作！！！！！！！！！！
		//静态成员函数不属于任何一个类对象，没有this指针，而非静态成员必须随类对象的产生而产生，所以静态成员函数"看不见"非静态成员，自然也就不能访问了
		//但是如果静态成员函数通过引用一个对象，是可以直接访问成员的，也体现了它成员函数的特权。
	}
	static int GetSum() {
		return Sum;
	}

private:
	static int N;
	static int Sum;
};

int Temp::N = 0;
int Temp::Sum = 0;

int Sum(int n) {
	Temp::Reset();//只能在全局域使用静态成员函数！！！！！！！！！！
	Temp* a = new Temp[n];
	delete[] a;
	a = NULL;
	return Temp::GetSum();
}

class Solution {
public:
	int Sum_Solution(int n) {
		return Sum(n);
	}
};


//2. 虚函数
class A;
A* Array[2];

class A {
public:
	virtual int Sum(int n) {
		return 0;
	}
};

class B : public A {
public:
	virtual int Sum(int n) {
		return Array[!!n]->Sum(n-1) + n;//!!n 表示两种选择，在两个函数中二选一
	}
};

class Solution {
public:
	int Sum_Solution(int n) {
		A a;
		B b;
		Array[0] = &a;
		Array[1] = &b;
		return Array[1]->Sum(n);
	}
};


//3. 函数指针
typedef int (*fun)(int n);

int Sum1(int n){
	return 0;
}

int Sum2(int n){
	static fun f[2]={Sum1,Sum2};
	return n+f[!!n](n-1);
}

class Solution {
public:
	int Sum_Solution(int n) {
		return Sum2(n);
	}
};


//4. 模板类型，实际上不可行
template<int n> struct Sum {
	enum Value { N = Sum<n - 1>::N +n };
};

template<> struct Sum<1> {
	enum Value { N = 1 };
};

class Solution {
public:
	int Sum_Solution(int n) {
		return Sum<100>::N;//这里必须要用常量100, const int m=n;也会报错
	}
};

int main() {
	Solution sol;
	cout<<sol.Sum_Solution(100);//这里的100没有意义
	return 0;
}


//5. 逻辑短路与
class Solution {
public:
    int Sum_Solution(int n) 
    {
        int res = n;
        n && (res = res + Sum_Solution(n-1));
        return res;
    }
};