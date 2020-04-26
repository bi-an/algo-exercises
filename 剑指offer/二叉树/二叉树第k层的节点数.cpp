struct Node
{
  int val;
  Node *left, *right;
  Node() : left(NULL), right(NULL), val(0) {}
  Node(int _val) : val(_val), left(NULL), right(NULL) {}
};

// 递归
// 当到达第k层，则如果这个节点不为null，那么返回1，然后回溯
// 父节点收集来自两个孩子收集的第k层的节点数，然后相加（冒号后面表示收集的k层节点的个数）
//   k=4
// 	 4				      1:3
//	 				    /    \
//	 3			     2:2      3:1
//				 /      \      /
//	 2			4:1      5:1  6:1
//			   / \	  	 /     \
//   1        7:1 NULL:0 8:1    9:1
//			 / \   	
int getKthNum(Node* root, int k){
if (root == nullptr)
  return 0;
if (root != nullptr && k == 1)
  return 1;
return getKthNum(root->left, k - 1) + getKthNum(root->right, k - 1);
}

// 非递归
int getKthNumOfNode(Node *root, int k)
{
  if (root == nullptr || k < 0)
    return -1;
  queue<Node *> Q;
  Q.push(root);
  int cnt = 0;
  while (!Q.empty())
  {
    if (cnt == k)
    {
      return Q.size();
    }
    int width = Q.size();
    for (int i = 0; i < width; i++)
    {
      Node *par = Q.front();
      if (par->left)
        Q.push(par->left);
      if (par->right)
        Q.push(par->right);
      Q.pop();
    }
    cnt++;
  }
  return -1;
}