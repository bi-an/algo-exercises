#pragma once
#include <vector>
#include <list>
#include <algorithm>
#include <string>

template <typename T> class HashTable {
public:
	// 哈希桶个数是质数
	// explicit: 如果T是int，那么HashTable(10)有可能是调用复制构造函数，这里禁止这种隐式转化
	// 装填因子为1，如果超过1就再散列
	explicit HashTable(int size = 101):currentSize(0), theLists(size) { // std::vector的构造函数是explicit的，100是分配内存大小，不存在歧义

	}

	bool contains(const T& x) const{
		const std::list<T> &whichList = theLists[myhash(x)]; // 链表桶
		return std::find(whichList.begin(), whichList.end(), x) != whichList.end();
	}

	void makeEmpty() {
		for (int i = 0; i < theLists.size(); i++)
			theLists[i].clear();
	}

	bool insert(const T& x) {
		std::list<T> &whichList = theLists[myhash(x)]; // 这里必须是引用
		if (contains(x))
			return false;

		whichList.push_back(x);

		if (++currentSize > theLists.size())
			rehash(); 

		return true;
	}

	bool remove(const T& x) {
		std::list<T> &whichList = theLists[myhash(x)];
		auto itr = std::find(whichList.begin(), whichList.end(), x); // 这里必须用auto，std::list<T>::iterator会报错
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
			theLists[i].clear(); // 之前的位置全部要重新计算
		currentSize = 0;
		for (int i = 0; i < theLists.size(); i++) {
			auto itr = oldLists[i].begin();
			while(itr!=oldLists[i].end())
				insert(*itr++);
		}
	}

	// 计算key
	int myhash(const T& x) const {
		int hashVal = hash(x); // TODO: 由外部提供
		hashVal %= theLists.size();
		if (hashVal < 0) { // 如果溢出，那么可能为负数
			hashVal += theLists.size();
		}
		return hashVal;
	}

};

// 外部函数
static int hash(const std::string& key, size_t tableSize) {
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal += 37 * hashVal + key[i];
	hashVal %= tableSize;
	if (hashVal < 0) // 如果溢出，将有可能得到负数
		hashVal += tableSize;

	return hashVal;
}

static int hash(int key) {
	return 0; // TODO
}

static int nextPrime(int x) {
	// TODO

}