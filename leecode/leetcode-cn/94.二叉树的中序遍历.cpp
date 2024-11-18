// 递归法
// 时间复杂度 O(n)
// 空间复杂度 O(n)
// TODO

// 迭代法
// 时间复杂度 O(n)
// 空间复杂度 O(n)
class Solution
{
 public:
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> res;
    stack<TreeNode *> stk;
    // Q: 能否先将 root 压栈，然后外部循环条件改为“栈非空”？
    // A: 不能。虽然从 root 出发一路向左都压栈了，但是如果压栈后，栈内只有一个节点，
    // 也就是没有左节点时，由于我们在本次循环内立即弹栈，导致下一次循环时栈为空，外部循环退出。
    // 显然，如果此时还有右节点，外部循环还应该继续。
    // 详见“迭代法 写法二”。
    while (root != nullptr || !stk.empty())
    {
      // 从 root 出发一路向左，全部压栈
      while (root != nullptr)
      {
        stk.push(root);
        root = root->left;
      }
      root = stk.top();
      stk.pop();
      res.push_back(root->val);
      // 即使 root->right 为 NULL 也必须赋值一次，
      // 否则 root 永远不等于 NULL，导致 while 循环永不终止。
      root = root->right;
    }
    return res;
  }
};

// 迭代法 写法二
class Solution
{
 public:
  vector<int> inorderTraversal(TreeNode *root)
  {
    vector<int> res;
    stack<TreeNode *> stk;
    // 压入 root
    if (root)
      stk.push(root);
    while (!stk.empty())
    {
      // 由于 root 已经压栈过了，这里只压入左节点
      while (root && root->left)
      {
        root = root->left;
        stk.push(root);
      }
      root = stk.top();
      res.push_back(root->val);
      stk.pop();
      // 如果还有右节点，应该在此处压栈，防止栈为空而提前退出循环
      if (root->right)
      {
        // 压入右节点，现在节点是根
        root = root->right;
        stk.push(root);
      }
      else
      {
        root = nullptr; // 标记 root 已经被访问过，防止重复访问
      }
    }
    return res;
  }
};

// Morris 中序遍历
// 时间复杂度 O(n)
// 空间复杂度 O(1)
// 参见 官方题解
// TODO