#include <iostream>
#include <map>
#include <stdlib.h>
using namespace std;

struct Array
{
  int *data;
  int size;
  int offset;
};

// 以下函数与c++11同名函数作用相同
template <typename T>
void make_heap(T *data, int size, bool (*comp)(const T &a, const T &b));

template <typename T>
void pop_heap(T *data, int size);

template <typename T>
void push_heap(T *data, int size);

bool comp(const Array &a, const Array &b)
{
  return a.data[a.offset] > b.data[b.offset];
}

bool sort(int *out, int size, int **in, int n, int *lens)
{
  if (out == nullptr || in == nullptr || lens == nullptr || size <= 0
      || size < n || n <= 0)
    return false;
  int actual_len = 0;
  for (int i = 0; i < n; ++i)
  {
    actual_len += lens[i];
  }
  if (size < actual_len)
    return false;

  Array *heap = new Array[n];
  for (int i = 0; i < n; ++i)
  {
    heap[i] = { in[i], lens[i], 0 };
  }
  make_heap(heap, n, comp);
  int i = 0;
  while (n > 0)
  {
    Array cur = heap[0];
    pop_heap(heap, n);
    out[i++] = cur.data[cur.offset];
    cur.offset++;
    if (cur.offset < cur.size)
    {
      heap[n - 1] = cur;
      push_heap(heap, n);
    }
    else
    {
      --n;
    }
  }
  return true;
}

#define SIZE(data) (sizeof(#data) / sizeof(int))

// 正确的输入
void test1()
{
  int data1[] = { 1, 2, 3, 5 };
  int data2[] = { 3, 5, 67 };
  int data3[] = { 1, 8, 10 };

  int *data[3] = { data1, data2, data3 };
  int lens[3] = { SIZE(data1), SIZE(data2), SIZE(data3) };
  int size = SIZE(data1) + SIZE(data2) + SIZE(data3);
  int *result = new int[size];
  bool success = sort(result, size, data, 3, lens);
  cout << "test1 " << (success ? "success" : "fail");
  if (success)
  {
    cout << " : ";
    for (int i = 0; i < size; i++)
    {
      cout << result[i] << ", ";
    }
  }
  cout << endl;
}

// 错误的输入
void test2()
{
  int data1[] = { 1, 2, 3, 5 };
  int data2[] = { 3, 5, 67 };
  int data3[] = { 1, 8, 10 };

  int *data[3] = { data1, data2, data3 };
  int lens[3] = { SIZE(data1), SIZE(data2), SIZE(data3) };
  int size = SIZE(data1) + SIZE(data2) + SIZE(data3);
  int *result = new int[size];
  bool success = sort(result, size - 1, data, 3, lens);
  cout << "test2 " << (success ? "success" : "fail");
  if (success)
  {
    cout << " : ";
    for (int i = 0; i < size; i++)
    {
      cout << result[i] << ", ";
    }
  }
  cout << endl;
}

// 错误的输入
void test3()
{
  int data1[] = { 1, 2, 3, 5 };
  int data2[] = { 3, 5, 67 };
  int data3[] = { 1, 8, 10 };

  int *data[3] = { data1, data2, data3 };
  int lens[3] = { SIZE(data1), SIZE(data2), SIZE(data3) };
  int size = SIZE(data1) + SIZE(data2) + SIZE(data3);
  int *result = new int[size];
  bool success = sort(result, size - 1, data, 3, NULL);
  cout << "test3 " << (success ? "success" : "fail");
  if (success)
  {
    cout << " : ";
    for (int i = 0; i < size; i++)
    {
      cout << result[i] << ", ";
    }
  }
  cout << endl;
}

int main()
{

  test1();
  test2();
  test3();

  return 0;
}
