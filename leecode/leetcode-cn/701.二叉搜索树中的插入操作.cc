class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root == nullptr) 
            return new TreeNode(val);

        if(val < root->val)
            root->left = insertIntoBST(root->left, val);
        else if(val > root->val)
            root->right = insertIntoBST(root->right, val);
        // 一般插入的val与其他节点不相等    

        return root;
    }
};