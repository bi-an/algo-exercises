#pragma once

// AVL树是平衡的BST树(任何节点都是平衡的)
// 高度是O(logN)
template<typename T> class AVLTree{
public:
	AVLTree(){}
	AVLTree(const AVLTree& rhs){

	}
	~AVLTree(){
		makeEmpty();
	}

	const T& findMin() const; // 什么情况下不能返回引用?
	const T& findMax() const;
	bool contains(const T& x) const;
	bool isEmpty() const;
	void printTree() const;

	void makeEmpty();
	void insert(const T& x);
	void remove(const T& x);
	int getHeight() const;

	const AVLTree& operator=(const AVLTree& rhs);

private:
	struct AVLNode{
		T val;
		AVLNode *left;
		AVLNode *right;
		int height;
	};	

	AVLNode *root;

	int getHeight(AVLNode<T> *t) const;
	AVLNode* rotateLeft(AVLNode * nodeN); // 可以用*&
	AVLNode* rotateRight(AVLNode * nodeN);
	AVLNode* rotateLeftRight(AVLNode *nodeN);
	AVLNode* rotateRightLeft(AVLNode *nodeN);

	void insert(const T& x, AVLNode *&t) const; // 用引用参数可以修改root
	void remove(const T& x, AVLNode *&t) const;
	AVLNode* findMin(AVLNode *t) const;
	AVLNode* findMax(AVLNode *t) const;
	bool contains(const T& x, AVLNode* t) const;
	void makeEmpty(AVLNode *&t) const;
	void printTree(AVLNode *t) const;
	AVLNode* clone(AVLNode *t) const;
	AVLNode* rebalance(AVLNode *t);

};


// 找到第一个不平衡的节点nodeN
// nodeC=nodeN的左孩子
// nodeN的左孩子=nodeC的右孩子
// nodeC的右孩子=nodeN
// return nodeC
template<typename T> AVLNode* AVLTree<T>::rotateRight(AVLNode *nodeN){
	AVLNode *nodeC=nodeN->left;
	nodeN->left=nodeC->right;
	nodeC->right=nodeN;
	// 高度更新
	nodeC->height=std::max(getHeight(nodeC->left),getHeight(nodeC->right))+1; // 有没有必要这么求？直接用getHeight(nodeC)行不行？
	nodeN->height=std::max(getHeight(nodeN->left),nodeC->height)+1; // nodeN的右孩子是nodeC
	return nodeC;
}

template<typename T> AVLNode* AVLTree<T>::rotateLeft(AVLNode *nodeN){
	AVLNode *nodeC=nodeN->right;
	nodeN->right=nodeC->left;
	nodeC->left=nodeN;
	// 高度更新
	// TODO
	return nodeC;
}

template<typename T> AVLNode* AVLTree<T>::rotateRightLeft(AVLNode *nodeN){
	
}

// 对于空树，不能访问t->height，所以使用getHeight()函数更安全
template<typename T> int AVLTree<T>::getHeight(AVLNode *t) const{
	return t==nullptr?0:t->height;
}

template<typename T> void AVLTree<T>::insert(const T& x, AVLNode*& t) const{
	
}

template<typename T> AVLNode