// 前缀和 + 哈希表 + DFS
// 时间复杂度：O(N)，每个节点访问一次。
// 空间复杂度：O(Height)，最坏情况下为链表，Height = N；最好情况下为平衡二叉树，Height = logN。
class Solution {
    // 一边先序访问节点，一边保存当前节点到 root 之间路径的前缀和。
    unordered_map<long long, int> preSum; // 前缀和的计数
    int sum;

public:
    int pathSum(TreeNode* root, int sum) {
        this->sum = sum;
        // 初始化为 1：
        // 假设有个 nil 节点，用于当前节点的值恰好等于 sum 的情况。
        // 此时，nil 节点和当前节点恰好组成一条路径。
        preSum[0] = 1;
        return dfs(root, 0);
    }

    // @return 以 root 结尾的路径和等于 sum 的路径数
    // cur 是上一次的前缀和。
    // 先序遍历
    int dfs(TreeNode* root, int cur) {
        if (root == nullptr)
            return 0;
        
        cur += root->val;
        int ret = 0;
        // 如果存在 cur - sum 的前缀和的节点，
        // 那么该节点（不包含自身）到当前节点之间的路径，前缀和为 sum.
        // 注意：不能先记录 preSum[cur] 再去寻找 preSum[cur - sum]，
        // 因为 cur - sum 本身就意味着当前节点计入路径尽头，只能寻找其他节点构成起点。
        if (preSum.count(cur - sum))
            ret = preSum[cur - sum];
        
        preSum[cur]++; // 全局变量记录当前遍历到的前缀和
        ret += dfs(root->left, cur);
        ret += dfs(root->right, cur);
        preSum[cur]--; // 从全局变量中删去本次的前缀和，因为路径只能自顶而下，下一次将访问 root 的右兄弟

        return ret;
    }
};

// 解法二：两重 DFS
// 时间复杂度：O(N^2)，因为有两重 DFS。
// 空间复杂度：O(N)，递归深度。
class Solution {
public:
    int pathSum(TreeNode* root, int sum) {
        if (root == nullptr)
            return 0;
        
        int res = dfs(root, sum);
        res += pathSum(root->left, sum) + pathSum(root->right, sum);
        return res;
    }

    // @return 以 root 为起点的路径和为 sum 的路径数。
    int dfs(TreeNode* root, int sum) {
        if (root == nullptr)
            return 0;
        int ret = 0;
        if (sum == root->val)
            ret += 1; // 注意不能 return，因为再接上一段和为 0 的路径，也可以构成总和为 sum 的路径。

        sum -= root->val;
        ret += dfs(root->left, sum);
        ret += dfs(root->right, sum);
        return ret;
    }
};