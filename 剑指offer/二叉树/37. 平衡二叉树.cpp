//基于后序遍历，每个节点只访问一次
class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
    	if(!pRoot) return true;
    	int depth=0;
    	return IsBalanced_Solution(pRoot,&depth);
    }

    bool IsBalanced_Solution(TreeNode* pRoot, int *pDepth) {
    	if(!pRoot){
    		*pDepth=0;
    		return true;
    	}
    	int left,right;
    	if(IsBalanced_Solution(pRoot->left,&left) && IsBalanced_Solution(pRoot->right,&right)){
    		int diff=left-right;
    		if(diff<=1 && diff>=-1){
    			*pDepth=1+(left>right?left:right);
    			return true;
    		}
    	}
    	return false;
    }
};

//每次访问树的深度，这样节点会被重复访问
class Solution {
public:
    bool IsBalanced_Solution(TreeNode* pRoot) {
    	if(!pRoot) return true;
    	int left=TreeDepth(pRoot->left);
    	int right=TreeDepth(pRoot->right);
    	int diff=left-right;
    	if(diff>1 || diff<-1)
    		return false;
    	return true;
    }

    int TreeDepth(TreeNode* pRoot){
    	if(!pRoot) return 0;
    	int left=TreeDepth(pRoot->left);
    	int right=TreeDepth(pRoot->right);
    	return 1+(left>right?left:right);
    }
}