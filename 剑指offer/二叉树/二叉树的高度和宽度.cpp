struct TreeNode{
	int val;
	TreeNode *left;
	TreeNode *right;

	TreeNode(int x):
		val(x),left(NULL),right(NULL){
	}
};

//二叉树的高度，递归
int TreeHeight(TreeNode* pRoot){
	if(pRoot==NULL) return 0;

	int leftH=TreeHeight(pRoot->left);
	int rightH=TreeHeight(pRoot->right);

	return (leftH>rightH?leftH:rightH)+1; // 最后加上的这个1表示root节点占一个高度单位
}

//队列保存每一层
int TreeHeight(TreeNode* pRoot){
	if(!pRoot) return 0;
	std::queue<TreeNode*> Q;
	Q.push(pRoot);
	//int width=Q.size();
	int height=0;
	while(!Q.empty()){
		height++;
		int width = Q.size();
		for(size_t i=0;i<width;i++){
			TreeNode *p=Q.front();
			Q.pop();
			if(p->left) Q.push(p->left);
			if(p->right) Q.push(p->right);
		}
	}
	return height;
}

//树的宽度
int TreeWidth(TreeNode *pRoot){
	if(!pRoot) return 0;
	std::queue<TreeNode*> Q;
	Q.push(pRoot);
	int maxWidth=0;
	while(!Q.empty()){
		int width=Q.size();
		if(width>maxWidth) maxWidth=width;
		for(size_t i=0;i<width;i++){
			TreeNode* p=Q.front();
			Q.pop();
			if(p->left) Q.push(p->left);
			if(p->right) Q.push(p->right);
		}
	}
	return maxWidth;
}