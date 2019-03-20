#pragma once
#include <iostream>
using namespace std;

class NoMem {
public:
	NoMem() {
		cout << "NoMem()" << endl;
	}
};

class OutOfBounds {
public:
	OutOfBounds() {
		cout << "OutOfBounds()" << endl;
	}
};

//int OutOfBounds() {
//	return -1;
//}

template<class T>
class MaxHeap {
public:
	MaxHeap(int MaxHeapSize = 10);
	~MaxHeap() { delete[] heap; }
	int Size() const { return CurrentSize; }
	T Max() {
		if (CurrentSize == 0) {
			throw OutOfBounds();
		}
		return heap[1];
	}
	MaxHeap<T>& Insert(const T& x);
	MaxHeap<T>& DeleteMax(T& x);
	void Initialize(T a[], int size, int ArraySize);
	void Deactivate() { heap = 0; }
	void Output() const;
private:
	int CurrentSize, MaxSize;
	T *heap;
};
template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize)
{
	MaxSize = MaxHeapSize;
	heap = new T[MaxSize + 1]; //��0���ڵ㲻��
	CurrentSize = 0;
}
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
	if (CurrentSize == MaxSize)
		throw NoMem();
	//ΪxѰ��Ӧ�����λ��
	//i���µ�Ҷ�ڵ㿪ʼ��������������
	int i = ++CurrentSize;
	while (i != 1 && x > heap[i / 2])
	{
		heap[i] = heap[i / 2]; // ��Ԫ������
		i /= 2;              // ���򸸽ڵ�
	}
	heap[i] = x;
	return *this;
}
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{
	if (CurrentSize == 0)
		throw OutOfBounds();
	x = heap[1];
	T y = heap[CurrentSize--]; //���һ��Ԫ��
	// �Ӹ���ʼ, ΪyѰ�Һ��ʵ�λ��
	int i = 1,  // �ѵĵ�ǰ�ڵ�
		ci = 2;    // i���ӽڵ�
	while (ci <= CurrentSize)
	{
		// ʹheap[ci] ��i�ϴ���ӽڵ�
		if (ci < CurrentSize
			&& heap[ci] < heap[ci + 1])
			ci++;
		// �ܰ�y����heap[i]��?
		if (y >= heap[ci])
			break;//��
		//����
		heap[i] = heap[ci]; // �ӽڵ�����
		i = ci;             // ����һ��
		ci *= 2;
	}
	heap[i] = y;
	return *this;
}
template<class T>
void MaxHeap<T>::Initialize(T a[], int size, int ArraySize)
{
	delete[] heap;
	//heap = a;
	heap = new T[ArraySize + 1];
	for (int ii = 1; ii <= size; ii++) {
		heap[ii] = a[ii - 1];//�������³�ʼ���ķ�ʽ��ȫ�����Ǻ�ʱ //�ڶ��ַ�ʽ����heap��¶�������ߣ��õ�������ɸ���ʼֵ����
	}
	CurrentSize = size;
	MaxSize = ArraySize;
	// ����һ������
	// �ӵ�����һ�����ڵ㣨CurrentSize/2����ʼ����
	for (int i = CurrentSize / 2; i >= 1; i--)
	{
		T y = heap[i]; // �����ĸ�
		// Ѱ�ҷ���y��λ��
		int c = 2 * i; // c �ĸ��ڵ���y��Ŀ��λ��

		while (c <= CurrentSize)
		{
			// ʹheap[c]�ǽϴ���ӽڵ�
			if (c < CurrentSize
				&& heap[c] < heap[c + 1])
				c++;
			// �ܰ�y����heap[c/2]��?
			if (y >= heap[c])
				break;  // ��
			// ����
			heap[c / 2] = heap[c]; // �ӽڵ�����
			c *= 2;                 // ����һ��
		}
		heap[c / 2] = y;
	}
}
template<class T>
void MaxHeap<T>::Output() const
{
	cout << "The " << CurrentSize
		<< " elements are" << endl;
	for (int i = 1; i <= CurrentSize; i++)
		cout << heap[i] << ' ';
	cout << endl;
}