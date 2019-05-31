#pragma once
#include <exception>

template<typename T>
class Queue {
public:
	Queue() :data(new T[1]), m_front(0), m_back(0), m_capacity(1), m_size(0) {}
	~Queue() {
		for (int i = 0; i < m_capacity; i++)
			delete (data + i);
	}
	void push(T val) {
		if (m_size >= m_capacity)
			resize();
		m_front %= m_capacity;
		m_back %= m_capacity;
		data[m_back] = val;
		m_back++;
		m_size++;
	}
	void pop() {
		if (m_front >= 0 && m_front < m_back) {
			m_front++;
			m_front %= m_capacity;
			m_size--;
		}
		else
			throw std::exception("队列为空");
	}
	T front() {
		if (m_front >= 0 && m_front < m_back)
			return data[m_front];
		else
			throw std::exception("队列为空");
	}

	T back() {
		if (m_back < m_capacity && m_back>0)
			return data[m_back - 1];
		else
			throw std::exception("队列为空");
	}

	int size() {
		return m_size;
	}

	int capacity() {
		return m_capacity;
	}

private:
	T *data;
	int m_front;
	int m_back;
	int m_capacity;
	int m_size;

	void resize() {
		int sz = m_capacity * 2;
		T *data_new = new T[sz];
		for (int i = 0; i < m_capacity; i++) {
			data_new[i] = data[i];
		}
		for (int i = 0; i < m_capacity; i++)
			delete (data + i);
		m_capacity = sz;
		data = data_new;
	}
};


// 测试
#include <iostream>
using namespace std;

int main() {
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

	cout << "队列容量：" << Q.capacity() << endl;
	cout << "队列元素个数：" << Q.size() << endl;

	return 0;
}