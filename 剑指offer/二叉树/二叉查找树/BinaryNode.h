#pragma once

template<class T> class BinaryNode{
private:
	T data;
	BinaryNode *leftChild;
	BinaryNode *rightChild;

public:
	BinaryNode():leftChild(nullptr),rightChild(nullptr){

	}

	BinaryNode(int x):BinaryNode(x,nullptr,nullptr){

	}

	BinaryNode(T dataPortion, BinaryNode *newLeftChild, BinaryNode *newRightChild){
		data=dataPortion;
		leftChild=newRightChild;
		rightChild=newRightChild;
	}

	T getData(){
		return data;
	}	
};