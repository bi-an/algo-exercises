/**
 * 给定一个二叉树，编写一个函数来获取这个树的最大宽度。树的宽度是所有层中的最大宽度。这个二叉树与满二叉树（full binary tree）结构相同，
 * 但一些节点为空。
 * 
 * 每一层的宽度被定义为两个端点（该层最左和最右的非空节点，两端点间的null节点也计入长度）之间的长度。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/maximum-width-of-binary-tree
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
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
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root==nullptr) return 0;
        queue<pair<TreeNode*,unsigned long long>> Q;
        Q.push(make_pair(root, 1));
        int maxWidth = 1;
        while(!Q.empty()){
            int curWidth = (int)(Q.back().second - Q.front().second + 1);
            if(curWidth > maxWidth)
                maxWidth = curWidth;
            int sz = Q.size();    
            for(int i = 0; i < sz; i++){
                auto curPair = Q.front();
                TreeNode * node = curPair.first;
                unsigned long long id = curPair.second;
                Q.pop();
                if(node->left)
                    Q.push(make_pair(node->left, id*2)); // int*2可能溢出，所以id类型使用unsigned long long
                if(node->right)
                    Q.push(make_pair(node->right, id*2+1));
            }
        }
        return maxWidth;
    }
};