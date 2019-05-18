#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <string>

template <typename T> class HashTable {
public:
	// ��ϣͰ����������
	// explicit: ���T��int����ôHashTable(10)�п����ǵ��ø��ƹ��캯���������ֹ������ʽת��
	// װ������Ϊ1���������1����ɢ��
	explicit HashTable(int size = 101):currentSize(0), theLists(size) { // std::vector�Ĺ��캯����explicit�ģ�100�Ƿ����ڴ��С������������

	}

	bool contains(const T& x) const{
		const std::list<T> &whichList = theLists[myhash(x)]; // ����Ͱ
		return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
	}

	void makeEmpty() {
		for (int i = 0; i < theLists.size(); i++)
			theLists[i].clear();
	}

	bool insert(const T& x) {
		std::list<T> &whichList = theLists[myhash(x)]; // �������������
		if (contains(x))
			return false;

		whichList.push_back(x);

		if (++currentSize > theLists.size())
			rehash(); 

		return true;
	}

	bool remove(const T& x) {
		std::list<T> &whichList = theLists[myhash(x)];
		auto itr = std::find(whichList.begin(), whichList.end(), x); // ���������auto��std::list<T>::iterator�ᱨ��
		if (itr == whichList.end())
			return false;
		whichList.erase(itr);
		--currentSize;
		return true;
	}

private:
	std::vector<std::list<T>> theLists;
	int currentSize;

	void rehash() {
		std::vector<std::list<T>> oldLists = theLists;
		theLists.resize(nextPrime(2 * theLists.size())); // TODO: nextPrime()
		for (int i = 0; i < theLists.size(); i++) // makeEmpty()
			theLists[i].clear(); // ֮ǰ��λ��ȫ��Ҫ���¼���
		currentSize = 0;
		for (int i = 0; i < theLists.size(); i++) {
			auto itr = oldLists[i].begin();
			while(itr!=oldLists[i].end())
				insert(*itr++);
		}
	}

	// ����key
	int myhash(const T& x) const {
		int hashVal = hash(x); // TODO: ���ⲿ�ṩ
		hashVal %= theLists.size();
		if (hashVal < 0) { // ����������ô����Ϊ����
			hashVal += theLists.size();
		}
		return hashVal;
	}

};

// �ⲿ����
static int hash(const std::string& key, size_t tableSize) {
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal += 37 * hashVal + key[i];
	hashVal %= tableSize;
	if (hashVal < 0) // �����������п��ܵõ�����
		hashVal += tableSize;

	return hashVal;
}

static int hash(int key) {
	return 0; // TODO
}

static int nextPrime(int x) {
	// TODO

}