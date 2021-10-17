// 中序遍历；迭代法
class Solution {
    public int kthSmallest(TreeNode root, int k) {
        Stack<TreeNode> S = new Stack<>();
        while(!S.empty() || root != null) {
            while(root != null) {
                S.push(root);
                root = root.left;
            }
            root = S.pop();
            if(--k == 0)
                return root.val;
            root = root.right;
        }
        return -1;
    }
}

// 比较丑的递归写法
// 注意到，该递归写法有很多重复计算
class Solution {
    private int ans = -1;
    private int cnt = 1;

    public int kthSmallest(TreeNode root, int k) {
        if(root == null)
            return -1;
        kthSmallest(root.left, k);
        if(cnt++ == k) {
            ans = root.val;
            return ans; // 提前终止，好像并没有提高计算效率
        }
        kthSmallest(root.right, k);
        return ans;
    }
}

// 改进：如果需要频繁求解第k大的数，怎么改进？
// 我们之所以需要频繁访问二叉树，是因为不知道其左右子树的节点数
// 我们可以在第一次访问时，记录下以每个节点为根的子树的节点数
