#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int M, N; // N个数，M轮
	cin >> N >> M;
	vector<int> num;
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		num.push_back(temp);
	}
	sort(num.begin(), num.end());
	long long minSum = 0;

	vector<int> select(num.begin(),num.begin()+2*M);

	for (int i = 0; i < M; i += 1) {
		int j = 2 * M - 1 - i;
		minSum += (long long)select[i] * select[j]; // 相乘也会溢出么？ 通过30%，可能是因为select没有强制转化成long long，现改正之
	}

	cout << minSum << endl;

	return 0;
}