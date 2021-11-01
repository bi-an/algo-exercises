#define _CRT_SECURE_NO_WARNINGS 
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;


// @Attention 仅供测试
void printAll(string name, vector<int>& nums) {
	cout << name << " : ";
	for (int i = 0; i < nums.size(); i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
}

static const int N = 1000000;
static const int MOD = 1000000007;

// Fenwick树，俗称树状数组
// 也就是二叉索引树(Binary Indexed Tree, BIT)
class BinaryIndexedTree
{
public:
	BinaryIndexedTree()
	{
		tree.assign(N + 1, 0);
	}
	// 找出第x个前缀和
	int ask(int x)
	{
		int ans = 0;
		while (x > 0)
		{
			ans = (ans + tree[x]) % MOD;
			x -= lowbit(x);
		}
		return ans;
	}
	// 第x个数加上k
	void add(int x, int k)
	{
		while (x <= tree.size())
		{
			tree[x] = (tree[x] + k) % MOD;
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
	int numWays(vector<int>& sales)
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
			ans = (ans + (long)left[i] * right[i] % MOD) % MOD; // 注意乘法可能会溢出
		}
		return ans;
	}

private:
	int n;
	vector<int> countLarger(vector<int>& sales)
	{
		vector<int> ans(n);
		BinaryIndexedTree tree;
		for (int i = 0; i < n; i++)
		{
			int x = N + 1 - sales[i];
			ans[i] = (ans[i] + tree.ask(x - 1)) % MOD;
			tree.add(x, 1);
		}
		// printAll("countLarger", ans); // TODO
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
	FILE* fp = freopen("E:/Code/CppProjects/Project1/Project1/in.txt", "r", stdin);

	int m; // m次测试
	cin >> m;
	while (m-- > 0)
	{
		test();
	}
	return 0;
}