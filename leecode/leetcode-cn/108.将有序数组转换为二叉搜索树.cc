// 时间复杂度：O(n)
// 空间复杂度：O(logn)，栈的深度取决于二叉搜索树的高度。
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums, 0, (int)nums.size() - 1);
    }

    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, start, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, end);
        return root;
    }
};