#pragma once
#include "BinaryNode.h"

template<typename T> class BinarySearchTree{
public:
	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& rhs);
	~BinarySearchTree();

	const T& findMin() const;
	const T& findMax() const;
	bool contains(const BinarySearchTree& x) const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty();
	void insert(const T& x);
	void remove(const T& x);

	const BinarySearchTree& operator=(const BinarySearchTree & rhs); // 为什么要返回const引用呢，这里的const和引用似乎都没有起到作用

private:
	BinaryNode *root;

	void insert(const T& x, BinaryNode* &t) const; // 为什么要用指针的引用呢，是为什么改变指针吗，还是为什么不改变指针？
	void remove(const T& x, BinaryNode* &t) const; // 万一要删除根呢？const怎么办？
	BinaryNode* findMin(BinaryNode* t) const;
	BinaryNode* findMax(BinaryNode* t) const;
	bool contains(const T& x, BinaryNode* t) const;
	void makeEmpty(BinaryNode* &t) const;
	void printTree(BinaryNode *t) const;
	BinaryNode* clone(BinaryNode *t) const;
};