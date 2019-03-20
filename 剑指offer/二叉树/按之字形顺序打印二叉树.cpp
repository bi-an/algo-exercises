// @Athor zzg
class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
    	vector<vector<int>> res;
    	if(pRoot==nullptr) return res;

    	TreeNode *p=pRoot;
		queue<TreeNode*> que;
		que.push(p);
		bool dir=true; //true从左往右
		while(!que.empty()){
			int width=que.size();
			vector<int> row;
			for(int i=0;i<width;i++){
				p=que.front();
				que.pop();
				row.push_back(p->val);
				if(p->left) que.push(p->left);
				if(p->right) que.push(p->right);
			}
			if(dir){
				res.push_back(row);
			}
			else{
				vector<int> anti_row;
				for(int i=width-1;i>=0;i--){
					anti_row.push_back(row[i]);
				}
				res.push_back(anti_row);
			}
			dir=!dir;
		}  
		return res;  	
    }
};

// 剑指offer用双栈实现，待填充。