class Solution {
public:
	//第一步：寻找根节点，这是遍历问题
	bool HasSubtree(TreeNode* parent, TreeNode* child)
	{
		if (parent == NULL || child == NULL)//约定空树不是任何树的子结构
			return false;

		if (DoesParentHasChild(parent, child))
			return true;
		else {
			return HasSubtree(parent->left, child) || HasSubtree(parent->right, child); // 其实这里的两个HasSubtree换成DoesParentHasChild也行，只是时间复杂度高一些
		}
	}
	
	//第二步：判断是否是子树，这是遍历问题
	bool DoesParentHasChild(TreeNode* parent, TreeNode *child) {
		if (child == NULL)//child遍历完，说明child所有节点都在parent上，应该return true
			return true;
		else if (parent == NULL)//child还没遍历完，parent就遍历完了，所以为false
			return false;
		
		if (parent->val != child->val)
			return false;

		return DoesParentHasChild(parent->left, child->left) &&
			DoesParentHasChild(parent->right, child->right);
	}
};


//写法二：
class Solution{
public:
	bool HasSubtree(TreeNode *parent, TreeNode *child){
		if(parent == nullptr || child==nullptr)
			return false;
		bool result = false;
		if(parent->val == child->val){
			result = DoesParentHasChild(parent, child);
			if(!result)
				result = HasSubtree(parent->left, child);
			if(!result)
				result = HasSubtree(parent->right, child);
		}
		return result;
	}

	bool DoesParentHasChild(TreeNode *parent, TreeNode *child){
		if(child == nullptr)
			return true;
		if(parent == nullptr)
			return false;

		return parent->val == child->val
			&& DoesParentHasChild(parent->left, child->left)
			&& DoesParentHasChild(parent->right, child->right);
	}
};


// 写法3
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        bool res=false;
        if(pRoot1!=nullptr && pRoot2!=nullptr){
            if(pRoot1->val==pRoot2->val)
                 res=DoesTree1HasTree2(pRoot1,pRoot2);
            if(!res)
                 res=DoesTree1HasTree2(pRoot1->left,pRoot2) || DoesTree1HasTree2(pRoot1->right,pRoot2);
       }
        return res;
    }
    
    bool DoesTree1HasTree2(TreeNode *pRoot1, TreeNode *pRoot2){
        if(pRoot2==nullptr) return true; // pRoot2到达叶子节点
        if(pRoot1==nullptr) return false; // pRoot1到达叶子，而pRoot2还没有到达叶子
        if(pRoot1->val!=pRoot2->val) return false;
        
        bool bLeft=DoesTree1HasTree2(pRoot1->left,pRoot2->left);
        bool bRight=DoesTree1HasTree2(pRoot1->right,pRoot2->right);
        return bLeft && bRight;
    }
};