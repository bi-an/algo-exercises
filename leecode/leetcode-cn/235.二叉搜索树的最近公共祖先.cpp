// 方法一：一次遍历
// 如果 p、q 都在左子树上，找左子树；
// 如果 p、q 都在右子树上，找右子树；
// 否则 root 是分岔点，也就是最近的父节点。
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (true) {
            if (root->val < p->val && root->val < q->val)
                root = root->right;
            else if (root->val > p->val && root->val > q->val)
                root = root->left;
            else
                break;
        }
        return root;
    }
};

// 方法二：二次遍历
// 一次遍历找 p，一次遍历找 q.
// 该思路易于理解，但是较麻烦。
// TODO