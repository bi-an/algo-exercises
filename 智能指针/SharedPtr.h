#ifndef __Shared_Ptr
#define __Shared_Ptr

#include <iostream>

struct Count {
	int __use_count = 1;
	int __weak_count = 0;
	Count() {}
	Count(int uc, int wc):__use_count(uc), __weak_count(wc) {}
	Count(const Count& other) : __use_count(other.__use_count), __weak_count(other.__weak_count){}
};

template<typename T> class WeakPtr;

template<typename T>
class SharedPtr {
	T* m_data = nullptr;
	Count* m_cnt = nullptr;
public:
	//friend class WeakPtr<T>;
	template <typename Type> friend class WeakPtr;
	SharedPtr() {}
	SharedPtr(T* data_){
		if (data_ != nullptr) {
			m_cnt = new Count(1,0);
			m_data = data_;
		}
	}
	SharedPtr(const SharedPtr& other) : m_data(other.m_data), m_cnt(other.m_cnt) {
		(other.m_cnt->__use_count)++;
	}
	~SharedPtr() {
		if (m_cnt->__use_count > 0) {
			(m_cnt->__use_count)--;
		}
		if (m_cnt->__use_count == 0) {
			delete m_data;
			if (m_cnt->__weak_count == 0)
				delete m_cnt;
		}
	}
};

template<typename T>
class WeakPtr {
	T* m_data = nullptr;
	Count* m_cnt = nullptr;
public:
	WeakPtr() {}
	WeakPtr(const WeakPtr& other) {
		m_data = other.m_data;
		(other.m_cnt->__weak_count)++;
		m_cnt = other.m_cnt;
	}
	WeakPtr(const SharedPtr<T>& sp):m_data(sp.m_data), m_cnt(sp.m_cnt) {
		m_cnt->__use_count = sp.m_cnt->__use_count;
		sp.m_cnt->__weak_count++;
	}
	~WeakPtr() {
		if (m_cnt->__weak_count > 0) {
			(m_cnt->__weak_count)--;
		}
		if (m_cnt->__use_count == 0 && m_cnt->__weak_count == 0) {
			delete m_cnt;
		}
	}
	SharedPtr<T> lock() {
		SharedPtr<T> sp(m_data);
		m_cnt->__use_count++;
		sp.m_cnt = m_cnt;
		return std::move(sp);
	}
};

#endif