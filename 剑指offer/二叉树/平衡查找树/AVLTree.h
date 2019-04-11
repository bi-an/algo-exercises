#pragma once
#include <algorithm> // std::max

struct AVLNode{
	T val;
	AVLNode *left;
	AVLNode *right;
	int height; // 记录每个节点高度
	AVLNode(T x, AVLNode *lChild, AVLNode *rChild):val(x),left(lChild),right(rChild),height(1){}
	AVLNode():AVLNode(0){}
	AVLNode(T x):AVLNode(x,nullptr,nullptr){}
};	

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

	AVLNode *root;

	int getHeight(AVLNode *t) const;
	int getHeightDifference(AVLNode *t) const;
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

// 右旋转：结果是第一个不平衡点nodeN的左孩子nodeC成为父节点
// 找到第一个不平衡的节点nodeN
// nodeC=nodeN的左孩子
// nodeN的左孩子=nodeC的右孩子
// nodeC的右孩子=nodeN
// return nodeC
template<typename T> AVLNode* AVLTree<T>::rotateRight(AVLNode *nodeN){
	// 右旋转
	AVLNode *nodeC=nodeN->left;
	nodeN->left=nodeC->right;
	nodeC->right=nodeN;
	// 高度更新
	nodeC->height=std::max(getHeight(nodeC->left),getHeight(nodeC->right))+1; // 有没有必要这么求？直接用getHeight(nodeC)行不行？
	nodeN->height=std::max(getHeight(nodeN->left),nodeC->height)+1; // nodeN的右孩子是nodeC
	return nodeC; // 返回原来nodeN的左孩子
}

template<typename T> AVLNode* AVLTree<T>::rotateLeft(AVLNode *nodeN){
	AVLNode *nodeC=nodeN->right;
	nodeN->right=nodeC->left;
	nodeC->left=nodeN;
	// 高度更新
	// TODO
	return nodeC;
}

// 当向右孩子的左子树添加节点时，进行右-左旋转
template<typename T> AVLNode* AVLTree<T>::rotateRightLeft(AVLNode *nodeN){
	AVLNode* nodeC=nodeN->right;
	nodeN->right=rotateRight(nodeC); // 第一次对右孩子(nodeN->right)右旋转
	return rotateLeft(nodeN); // 第二次对nodeN左旋转
}

// 对于空树，不能访问t->height，所以使用getHeight()函数更安全
template<typename T> int AVLTree<T>::getHeight(AVLNode *t) const{
	return t==nullptr?0:t->height;
}

template<typename T> void AVLTree<T>::insert(const T& x, AVLNode*& t) const{
	// TODO
	if(t==nullptr)
		t=new AVLNode(x);
	else if(x<t->left){ // 向左子树插入
		insert(x,t->left);
		// 左子树的高度插入前最多比右子树小1，插入之后一定大于等于右子树高度；左子树高度插入前最多比右子树大1，插入之后最多比右子树大2
		if(getHeight(t->left)-getHeight(t->right)==2){
			if(t<t->left->val)
				rotateRight(t);
			else
				rotateLeftRight(t);
		} 
	}
	else if(x>t->right)
		insert(x,t->right);
	else
		; // Duplication; do nothing
	t->height=std::max(getHeight(t->left),getHeight(t->right))+1; // 不能使用getHeight(t)，因为此时t的height没有更新
}

template<typename T> AVLNode* AVLNode<T>::rebalance(AVLNode *t){ // 由于insert之前时平衡二叉查找树，所以t是最靠近的不平衡点
	int diffHeight=getHeightDifference(t);
	// left subtree is taller by more than 1
	// so addtition was in left tree
	if(diffHeight>1){
		// 由于t是最靠近的不平衡点，所以t->left是平衡的，并且其左右子树高度差一定为1(因为t是不平衡的)；
		// 由于插入之前t是平衡的，所以插入之前t->left左右子树高度差一定为0
		if(getHeightDifference(t->left)>0) // Addition was in left subtree of left child
			rotateRight(t);
		else
			rotateLeftRight(t);
	}
	else if(diffHeight<-1){
		if(getHeightDifference(t->left)<0)
			
	}
}

template<typename T> int AVLNode<T>::getHeightDifference(AVLNode *t) const{
	int diffH=0;
	if(t!=nullptr)
		diffH=getHeight(t->left)-getHeight(t->right);
	return diffH;
}