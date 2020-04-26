#pragma once
#include <cassert>
#include <iostream>

template <typename T>
class Queue
{
 public:
  Queue() : data(new T[1]), m_front(0), m_back(0), m_capacity(0), m_size(0) {}
  ~Queue()
  {
    delete[] data;
  }
  void push(T val)
  {
    if (m_size >= m_capacity) // 此时要预留空间以插入新元素，所以即使相等也需要扩容
      resize();
    data[m_back] = val;
    m_size++;
    m_back++;
    if (m_size != m_capacity) // 由于m_back指向后一个元素，如果队列元素个数与数组容量相等，m_back应该指向数组之后的位置，否则循环转移到数组首位
      m_back %= m_capacity;
    // if(m_size!=m_capacity && m_back==m_capacity)
    //		m_back=0; // 似乎与上面的是一样的
  }
  void pop()
  {
    assert(m_front != m_back); // 队列为空的标志：m_front==m_back
    m_front++;
    m_front %= m_capacity;
    m_size--;
    //else {
    //	fprintf(stderr, "队列为空");
    //	exit(1); // 个人认为exit比异常方便，stderr可以重定向 // 或者用assert
    //}
  }
  T front()
  {
    assert(m_front != m_back);
    return data[m_front];
  }

  int size()
  {
    return m_size;
  }

  int capacity()
  {
    return m_capacity;
  }

 private:
  T *data;
  int m_front; // 左闭右开区间，m_back指向下一个元素
  int m_back;
  int m_capacity; // 数组容量
  int m_size;     // 数组中存放的数字个数

  void resize()
  {
    int sz = m_capacity * 2;
    if (sz == 0) // 因为初始时，m_capacity=0
      sz = 1;
    T *data_new = new T[sz];
    if (m_back < m_front)
    {
      for (int i = m_front; i < m_capacity; i++) // 此时m_capacity==m_size
        data_new[i] = data[i];
      for (int i = 0; i < m_back; i++)
        data_new[i] = data[i];
    }
    else
    {
      for (int i = 0; i < m_capacity; i++)
        data_new[i] = data[i];
    }
    if (data != nullptr) // 允许delete nullptr; 但是不允许delete[] nullptr;
      delete[] data;
    m_capacity = sz;
    data = data_new;
  }
};

// 测试
using namespace std;
#include <queue>

int main()
{
  Queue<int> Q;
  Q.push(1);
  Q.push(2);
  cout << Q.front() << endl;
  Q.pop();
  cout << Q.front() << endl;
  Q.pop();

  Q.push(3);
  //cout << Q.size() << endl;
  cout << Q.front() << endl;
  Q.push(4);
  //cout << Q.size() << endl;
  Q.pop();
  cout << Q.front() << endl;
  Q.pop();

  cout << "队列容量：" << Q.capacity() << endl;
  cout << "队列元素个数：" << Q.size() << endl;

  //std::queue<int> Q2;
  //Q2.pop();

  return 0;
}