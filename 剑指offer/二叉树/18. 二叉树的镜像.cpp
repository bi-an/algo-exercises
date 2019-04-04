// struct TreeNode {
// 	int val;
// 	struct TreeNode *left;
// 	struct TreeNode *right;
// 	TreeNode(int x) :
// 			val(x), left(NULL), right(NULL) {
// 	}
// };

// 非递归
// 思路：从根节点开始，层序遍历，每层父节点交换其子节点。
// 效率较高
class Solution {
public:
  void Mirror(TreeNode *pRoot){
    	if(!pRoot) return;
    	std::queue<TreeNode*> Q;
    	Q.push(pRoot);
    	while(!Q.empty()){
    		int width=Q.size();
    		for(size_t i=0;i<width;i++){
    			TreeNode* p=Q.front();
    			if(p->left) Q.push(p->left);
    			if(p->right) Q.push(p->right);
    			//左右交换
    			TreeNode* pp=p->left;
    			p->left=p->right;
    			p->right=pp;
    			Q.pop();
    		}
    	}
    }
};

// @Athor zzg
// 思想如上； 效率没有上面高，因为把nullptr也放入了队列
class Solution{
public:
    void Mirror(TreeNode *pRoot){
        if(pRoot==nullptr) return;
        queue<TreeNode*> Q;
        Q.push(pRoot);
        while(!Q.empty()){
            int width=Q.size();
            for(int i=0;i<width;i++){
                TreeNode *p=Q.front();
                Q.pop();
                if(p){
                    swap(p->left,p->right);
                    if(p->left || p->right){
                        Q.push(p->left);
                        Q.push(p->right);
                    }
                }
            }
        }
    }
};

// @Athor zzg
// 递归
// 思路：前序遍历，每次将左右节点交换。
class Solution{
public:
    void Mirror(TreeNode *pRoot){
        if(pRoot==nullptr) return;
        swap(pRoot->left,pRoot->right);
        //if(pRoot->left)
        Mirror(pRoot->left);
        //if(pRoot->right)
        Mirror(pRoot->right);
    }
};

// @Athor zzg
// 非递归: 栈模拟递归
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot==nullptr) return;
        //swap(pRoot->left, pRoot->right);
        stack<TreeNode*> S;
        S.push(pRoot);
        while(!S.empty()){
            TreeNode* p=S.top();
            S.pop();
            swap(p->left,p->right);
            if(p->left)
                S.push(p->left);
            if(p->right)
                S.push(p->right);
        }
    }
};

// 非递归
// 用栈模拟递归
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot==nullptr) return;
        stack<TreeNode*> S;
        TreeNode *p=pRoot;
        while(p || !S.empty()){
            if(p){
                TreeNode *tmp=p->left;
                p->left=p->right;
                p->right=tmp;
                S.push(p->right);
                p=p->left;
            }
            else{
                p=S.top();
                p=p->left;
                S.pop();
            }
        }
    }
};