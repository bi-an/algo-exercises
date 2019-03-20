// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

// 注意：用前/后序遍历序列和中序遍历序列重建二叉树，要求没有数值相同的节点，
// 否则，在中序遍历序列中有一个以上的对应值，产生不确定性，这样二叉树不唯一。

// 如果有重复节点值，那么应该序列化二叉树，即把nullptr的信息也存起来。


//递归1
class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.size() == 0 || vin.size() == 0) {
			return NULL;
		}
		//获取根节点
		TreeNode* root = new TreeNode(pre[0]);
		//查找根节点在中序遍历中的位置
		int cur = -1;
		for (int i = 0; i < vin.size(); i++) {
			if (root->val == vin[i]) {
				cur = i;
				break;
			}
		}
		if (cur == -1) {
			return NULL;
		}
		//构建左子树
		vector<int> lin;
		for (int i = 0; i < cur; i++) {
			lin.push_back(vin[i]);
		}
		vector<int> lpre;
		for (int i = 1; i < lin.size() + 1; i++) {
			lpre.push_back(pre[i]);
		}

		root->left = reConstructBinaryTree(lpre, lin);

		//构建右子树
		vector<int> rin;
		for (int i = cur + 1; i < vin.size(); i++) {
			rin.push_back(vin[i]);
		}
		vector<int> rpre;
		for (int i = 1 + lin.size(); i < pre.size(); i++) {
			rpre.push_back(pre[i]);
		}

		root->right = reConstructBinaryTree(rpre, rin);
		return root;

	}
};

//递归2
class Solution{
public:
	TreeNode* ConstructCore
	(
		vector<int>& pre, int startPre, int endPre,
		vector<int>& vin, int startVin, int endVin
	) 
	{
		int value = pre[startPre];
		TreeNode *root = new TreeNode(value);
		if (endPre == startPre) {
			if (endVin == startVin && pre[startPre] == vin[startVin])
				return root;
			else
				return nullptr;
		}

		//在中序遍历表中找根节点
		int pos = startVin;
		while (pos <= endVin && vin[pos]!=value)
			pos++;
		
		if (pos > endVin)
			return nullptr;

		int len = pos - startVin;
		if (len > 0)
			root->left = ConstructCore(pre, startPre + 1, startPre + len, vin, startVin, startVin + len - 1);
		if (pos < endVin)
			root->right = ConstructCore(pre, startPre + len + 1, endPre, vin, pos + 1, endVin);

		return root;
	}

	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.empty() || vin.empty() || pre.size()!=vin.size())
			return nullptr;
		return ConstructCore(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
	}
};