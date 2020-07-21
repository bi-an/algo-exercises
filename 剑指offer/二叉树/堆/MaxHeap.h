#pragma once
#include <iostream>
using namespace std;

class NoMem
{
 public:
  NoMem()
  {
    cout << "NoMem()" << endl;
  }
};

class OutOfBounds
{
 public:
  OutOfBounds()
  {
    cout << "OutOfBounds()" << endl;
  }
};

//int OutOfBounds() {
//	return -1;
//}

template <class T>
class MaxHeap
{
 public:
  MaxHeap(int MaxHeapSize = 10);
  ~MaxHeap()
  {
    delete[] heap;
  }
  int Size() const
  {
    return CurrentSize;
  }
  T Max()
  {
    if (CurrentSize == 0)
    {
      throw OutOfBounds();
    }
    return heap[1];
  }
  MaxHeap<T> &Insert(const T &x);
  MaxHeap<T> &DeleteMax(T &x);
  void Initialize(T a[], int size, int ArraySize);
  void Deactivate()
  {
    heap = 0;
  }
  void Output() const;

 private:
  int CurrentSize, MaxSize;
  T *heap;
};
template <class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
  MaxSize = MaxHeapSize;
  heap = new T[MaxSize + 1]; //第0个节点不用
  CurrentSize = 0;
}
template <class T>
MaxHeap<T> &MaxHeap<T>::Insert(const T &x)
{
  if (CurrentSize == MaxSize)
    throw NoMem();
  //为x寻找应插入的位置
  //i从新的叶节点开始，并沿着树上升
  int i = ++CurrentSize;
  while (i != 1 && x > heap[i / 2])
  {
    heap[i] = heap[i / 2]; // 将元素下移
    i /= 2;                // 移向父节点
  }
  heap[i] = x;
  return *this;
}
template <class T>
MaxHeap<T> &MaxHeap<T>::DeleteMax(T &x)
{
  if (CurrentSize == 0)
    throw OutOfBounds();
  x = heap[1];
  T y = heap[CurrentSize--]; //最后一个元素
  // 从根开始, 为y寻找合适的位置
  int i = 1,  // 堆的当前节点
      ci = 2; // i的子节点
  while (ci <= CurrentSize)
  {
    // 使heap[ci] 是i较大的子节点
    if (ci < CurrentSize && heap[ci] < heap[ci + 1])
      ci++;
    // 能把y放入heap[i]吗?
    if (y >= heap[ci])
      break; //能
    //不能
    heap[i] = heap[ci]; // 子节点上移
    i = ci;             // 下移一层
    ci *= 2;
  }
  heap[i] = y;
  return *this;
}
template <class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
  delete[] heap;
  //heap = a;
  heap = new T[ArraySize + 1];
  for (int ii = 1; ii <= size; ii++)
  {
    heap[ii] = a[ii - 1]; //这种重新初始化的方式安全，但是耗时 //第二种方式：将heap暴露给调用者，让调用者完成赋初始值工作
  }
  CurrentSize = size;
  MaxSize = ArraySize;
  // 产生一个最大堆
  // 从倒数第一个父节点（CurrentSize/2）开始处理
  for (int i = CurrentSize / 2; i >= 1; i--)
  {
    T y = heap[i]; // 保存子树的根，避免交换，改为下沉
    // 寻找放置y的位置
    int c = 2 * i; // c 的父节点是y的目标位置

    while (c <= CurrentSize)
    {
      // 使heap[c]是较大的子节点
      if (c < CurrentSize && heap[c] < heap[c + 1])
        c++;
      // 能把y放入heap[c/2]吗?
      if (y >= heap[c])
        break; // 能
      // 不能
      heap[c / 2] = heap[c]; // 子节点上移
      c *= 2;                // 下移一层
    }
    heap[c / 2] = y;
  }
}
template <class T>
void MaxHeap<T>::Output() const
{
  cout << "The " << CurrentSize << " elements are" << endl;
  for (int i = 1; i <= CurrentSize; i++)
    cout << heap[i] << ' ';
  cout << endl;
}