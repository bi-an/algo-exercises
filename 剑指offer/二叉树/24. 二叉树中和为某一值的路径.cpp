/*
输入一颗二叉树的根节点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径：定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。
(注意: 在返回值的list中，数组长度大的数组靠前)
*/

// vector的push_back和pop_back可以用来作为栈
// STL的stack是容器适配器，而不是容器，
// 只要支持一系列方法的容器(empty,size,back,push_back,pop_back)，都能作为stack使用。
// template <class T, class Container = deque<T> > class stack;
// 当没有特殊指派，那么将使用deque作为stack的实际容器。

// 前序遍历。

// @Athor zzg
// 路径定义1：从根节点到其他节点（不一定终点是叶子节点）。（剑指offer上不是这么定义的）
class Solution
{
 public:
  vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
  {
    vector<vector<int>> res;
    if (root == nullptr)
      return res;

    FindPathCore(root, expectNumber, vector<int>(), 0, res);

    return res;
  }

  void FindPathCore(TreeNode *root, int expectNumber, vector<int> path, int sum, vector<vector<int>> &res)
  {
    sum += root->val;

    if (sum == expectNumber)
    {
      path.push_back(root->val);
      res.push_back(path);
      path.pop_back();
    }
    else if (sum < expectNumber)
    {
      path.push_back(root->val);
      if (root->left)
        FindPathCore(root->left, expectNumber, path, sum, res);
      if (root->right)
        FindPathCore(root->right, expectNumber, path, sum, res);
    }
  }
};

// @Athor zzg
// 路径定义2：从根节点到叶节点。
// TODO: "在返回值的list中，数组长度大的数组靠前"条件没有满足，但是能通过剑指offer测试。
// 修正方法，使用algorithm的排序，定义一个compare函数，bool comp(const vector<int>& vec1, const vector<int> &vec2){return vec1.size() < vec2.siz();}
class Solution
{
 public:
  vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
  {
    vector<vector<int>> res;
    if (root == nullptr)
      return res;

    FindPathCore(root, expectNumber, vector<int>(), 0, res);

    return res;
  }

  void FindPathCore(TreeNode *root, int expectNumber, vector<int> path, int sum, vector<vector<int>> &res)
  {
    sum += root->val;

    if (sum == expectNumber)
    {
      if (root->left == nullptr && root->right == nullptr)
      { //增加判断叶子节点的条件
        path.push_back(root->val);
        res.push_back(path);
      }
      else
        path.pop_back();
    }
    else if (sum < expectNumber)
    {
      path.push_back(root->val);
      if (root->left)
        FindPathCore(root->left, expectNumber, path, sum, res);
      if (root->right)
        FindPathCore(root->right, expectNumber, path, sum, res);
    }
  }
};

// @Athor zzg
// 引用传递
class Solution
{
 public:
  vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
  {
    vector<vector<int>> res;
    if (root == nullptr)
      return res;
    vector<int> path;
    //FindPathCore(root, expectNumber, vector<int>(), 0, res);
    FindPathCore(root, expectNumber, path, 0, res);

    return res;
  }

  void FindPathCore(TreeNode *root, int expectNumber, vector<int> &path, int sum, vector<vector<int>> &res)
  {
    sum += root->val;

    if (sum == expectNumber)
    {
      if (root->left == nullptr && root->right == nullptr)
      {
        path.push_back(root->val);
        res.push_back(path);
      }
      else
        path.pop_back();
    }
    else if (sum < expectNumber)
    {
      path.push_back(root->val);
      if (root->left)
        FindPathCore(root->left, expectNumber, path, sum, res);
      if (root->right)
        FindPathCore(root->right, expectNumber, path, sum, res);
    }
    path.pop_back(); // 回到父节点之前，要删除路径上当前节点
  }
};

// 非递归
class Solution
{
 public:
  vector<vector<int>> FindPath(TreeNode *root, int expectNumber)
  {
    vector<vector<int>> pathList;
    if (!root)
      return pathList;
    vector<int> path;
    findAllPath(root, expectNumber, path, pathList);
    return pathList;
  }

 private:
  //寻找所有路径（不一定满足条件）；当满足条件时，压栈
  void findAllPath(TreeNode *root, int expectNumber, vector<int> &path, vector<vector<int>> &pathList)
  { //本质是一个先序遍历
    path.push_back(root->val);
    if (root->left == nullptr && root->right == nullptr)
    { //判断是否是叶子节点
      int sum = 0;
      for (size_t i = 0; i < path.size(); i++)
      {
        sum += path[i];
      }
      if (sum == expectNumber)
      {
        pathList.push_back(path);
      }
    }
    if (root->left)
      findAllPath(root->left, expectNumber, path, pathList);
    if (root->right)
      findAllPath(root->right, expectNumber, path, pathList);
    path.pop_back(); //退回父节点
  }
};