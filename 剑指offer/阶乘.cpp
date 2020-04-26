#include <cmath>
#include <iostream>
using namespace std;
//#define SIZE 300

class Factorial
{
  static const int SIZE = 3000; //TODO

 public:
  void Print(long n)
  {
    int arr[SIZE] = { 0 };
    arr[0] = 1;
    for (long i = 2; i <= n; i++)
    {
      int carry = 0;
      for (int j = 0; j < SIZE; j++)
      {
        int temp = arr[j] * i + carry;
        arr[j] = temp % 10;
        carry = temp / 10;
      }
    }
    int pos = SIZE - 1;
    while (arr[pos] == 0)
    {
      pos--;
    }
    for (int i = pos; i >= 0; i--)
    {
      cout << arr[i];
    }
    cout << endl;
  }

  void Print(char n)
  {
    long num = n;
    Print(num);
  }
  void Print(short n)
  {
    long num = n;
    Print(num);
  }
  void Print(int n)
  {
    long num = n;
    Print(num);
  }

  void MaxFactOfInt()
  {
    int len = sizeof(int) * 8;
    int max = pow(2, len - 1) - 1;
    //cout << max;
    Print(max);
  }

  void MaxFactOfChar()
  {
    char len = sizeof(char) * 8;
    char max = pow(2, len - 1) - 1;
    //cout << max;
    Print(max);
  }

  void MaxFactOfUChar()
  {
    char len = sizeof(char) * 8;
    unsigned char max = pow(2, len) - 1;
    //cout << max;
    Print(max);
  }
};

int main(int argc, char **argv)
{
  Factorial sol;
  //char n = 5;
  //sol.Print(5);
  sol.MaxFactOfChar();
  // sol.MaxFactOfUChar();
  return 0;
}
