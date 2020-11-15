/*
从上往下打印出二叉树的每个节点，同层节点从左至右打印。
*/

/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};
*/

class Solution
{
 public:
  vector<int> PrintFromTopToBottom(TreeNode *root)
  {
    vector<int> vec;
    if (!root)
      return vec;
    queue<TreeNode *> Q;
    Q.push(root);
    while (!Q.empty())
    {
      size_t width = Q.size();
      //打印并压栈（准备打印下一层）
      for (size_t i = 0; i < width; i++)
      {
        TreeNode *pNode = Q.front();
        Q.pop();
        vec.push_back(pNode->val);
        if (pNode->left)
          Q.push(pNode->left);
        if (pNode->right)
          Q.push(pNode->right);
      }
    }
    return vec;
  }
};
