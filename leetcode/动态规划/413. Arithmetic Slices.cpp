/*
A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequence:
1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.
1, 1, 2, 5, 7

A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.

A slice (P, Q) of array A is called arithmetic if the sequence:
A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.

The function should return the number of arithmetic slices in the array A.

Example:
A = [1, 2, 3, 4]
return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/

// 递归，时间复杂度O(n)，因为递归函数slices至多被调用n次
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		sum = 0;
		slices(A, A.size() - 1);
		return sum;
	}

	int slices(vector<int>& A, int i) {
		// printf("%d ", i);
		if (i < 2)
			return 0;
		int ap = 0;
		if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
			ap = 1 + slices(A, i - 1);
			sum += ap;
		}
		else
			slices(A, i - 1); // 注意，此时不应该接受slices()的返回值
		return ap;
	}

private:
	int sum;
};

// 动态规划
// dp[i]表示i所在位置的(等差数列的连续个数-2)，当然要大于等于0
// 例如，一个连续的等差数列1,2,3,4,5，那么dp[i]分别为0,0,1,2,3，所含的所有子连续等差数列的个数为0+0+1+2+3=6
// 解释：假设有n个数连续，那么三个连续数的子列个数为n-2，四个连续数的子列个数为n-3，...，n个连续数的子列个数为1.
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int sum = 0;
		vector<int> dp(A.size(), 0);
		for (int i = 2; i < A.size(); i++) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
				dp[i] = dp[i - 1] + 1;
				sum += dp[i]; // 把所有的dp[i]全部加起来
			}
			else
				dp[i] = 0;
		}
		return sum;
	}
};

// 优化的动态规划
// 空间复杂度降低到O(1)
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int sum = 0, cur = 0; // 只用一个变量存储上一次结果即可
		for (int i = 2; i < A.size(); i++) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
				cur = cur + 1;
				sum += cur;
			}
			else
				cur = 0;
		}
		return sum;
	}
};