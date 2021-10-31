#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// @Attention 仅供测试
void printAll(string name, vector<int>& nums) {
    cout << name << " : ";
    for(int i=0;i<nums.size();i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

class TreeLikeArray
{
 public:
  TreeLikeArray(int n)
  {
    tree.resize(n + 1);
    tree.assign(n, 0);
  }
  // 找出第x个前缀和
  int ask(int x)
  {
    int ans = 0;
    while (x > 0)
    {
      ans += tree[x];
      x -= lowbit(x);
    }
    return ans;
  }
  // 第x个数加上k
  void add(int x, int k)
  {
    while (x <= tree.size())
    {
      tree[x] += k;
      x += lowbit(x);
    }
  }

 private:
  vector<int> tree;

  int lowbit(int x)
  {
    return x & -x;
  }
};

class Solution
{
 public:
  int numWays(vector<int> &sales)
  {
    n = sales.size();

    // printAll("sales", sales); // TODO
    // 计算左边大于当前数的个数
    vector<int> left = countLarger(sales);
    // 翻转sales
    std::reverse(sales.begin(), sales.end());
    // printAll("sales", sales); // TODO
    // 计算右边大于当前数的个数
    vector<int> right = countLarger(sales);
    // 翻转right
    std::reverse(right.begin(), right.end());

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans += left[i] * right[i];
    }
    return ans;
  }

 private:
  int n;
  vector<int> countLarger(vector<int> &sales)
  {
    vector<int> ans(n);
    TreeLikeArray tree(n);
    for (int i = 0; i < n; i++)
    {
      int x = n + 1 - sales[i];
      ans[i] += tree.ask(x);
      tree.add(x, 1);
    }
    // printAll("countLarger", sales); // TODO
    return ans;
  }
};

// @Attention 仅供测试
void test()
{
  int n;
  cin >> n;
  vector<int> sales(n);
  for (int i = 0; i < n; i++)
    cin >> sales[i];
  Solution sol;
  cout << sol.numWays(sales) << endl;
}
int main()
{
  int m; // m次测试
  cin >> m;
  while (m-- > 0)
  {
    test();
  }
}