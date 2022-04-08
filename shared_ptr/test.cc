#include <iostream>
using namespace std;

class B;

class A {
 public:
  A() { cout << "A()" << endl; }

 private:
  friend class B;
  int m1;
};

class B {
 public:
  void print(A a) {
    a.m1 = 10;
    cout << a.m1 << endl;
  }
};

int main() {
  B b;
  A a;
  b.print(a);
}