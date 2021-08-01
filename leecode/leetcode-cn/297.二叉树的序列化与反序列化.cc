/*
 * @Author: your name
 * @Date: 2021-08-01 20:24:03
 * @LastEditTime: 2021-08-01 20:24:37
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\297.cc
 */

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
	// 层序序列化
	static string serialize(TreeNode* root) {
		if (root == nullptr)
			return "[]";

		string str = "[";
		queue<TreeNode*> Q;
		Q.push(root);
		int count = 1; // 记录队列中非空节点的个数
		while (count > 0) {	// 只要当前队列中非空节点数大于0，说明当前的节点（不管是否为空）都要记录
			TreeNode* node = Q.front();
			Q.pop();

			if (node != root)
				str.append(",");
			
			if (node) {
				str.append(std::to_string(node->val));
				Q.push(node->left); // 不管是否为空，全部孩子塞进队列
				Q.push(node->right);
				count--; // 因为前面弹出了一个非空节点
				if (node->left) count++;
				if (node->right) count++;
			}
			else {
				str.append("null");
			}	
		}
		str += "]";
		return str;
	}

	static vector<string> split(string str, const char c) {
		vector<string> ans;

		str += c;
		int begin = 0, end = 0;
		while (end < str.size()) {
			if (str[end] != c) {
				end++;
				continue;
			}
			string cur = str.substr(begin, end - begin);
			ans.push_back(cur);
			begin = ++end;
		}

		return ans;
	}

	// 格式："[]", "[1,null,2]"
	// 非法格式："[null]", "[1,2,null]"
	static TreeNode* deserialize(string data) {
		if (data.size() <= 2) return nullptr;
		vector<string> strs = split(data.substr(1, data.size() - 2), ',');
		TreeNode* root = new TreeNode(atoi(strs[0].c_str()));
		queue<TreeNode*> Q;
		Q.push(root);
		int i = 0;
		while (!Q.empty()) {
			TreeNode* node = Q.front();
			Q.pop();
			if (++i < strs.size() && strs[i] != "null") {
				node->left = new TreeNode(atoi(strs[i].c_str()));
				Q.push(node->left);
			}
			if (++i < strs.size() && strs[i] != "null") {
				node->right = new TreeNode(atoi(strs[i].c_str()));
				Q.push(node->right);
			}
		}
		return root;
	}
};
// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));