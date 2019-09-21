
#include <iostream>
#include <vector>
using namespace std;

// 01背包求方案数

int main() {
	int K, A, X, B, Y;
	cin >> K >> A >> X >> B >> Y;

	vector<vector<int>> dp;
	vector<int> p(X + Y + 1);
	for (int i = 0; i < X + Y + 1; i++) {
		vector<int> temp(K + 1, 0);
		dp.push_back(temp);
	}
	dp[0][0] = 1; // 注意
	for (int i = 1; i <= X; i++)
		p[i] = A;
	for (int i = X + 1; i < X + Y + 1; i++)
		p[i] = B;

	for (int i = 1; i < X + Y + 1; i++) {
		for (int j = 0; j < K + 1; j++) {
			if (j >= p[i])
				dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - p[i]]) % 1000000007;
			else
				dp[i][j] = dp[i - 1][j];
		}
	}

	cout << dp[X + Y][K];

	return 0;
}