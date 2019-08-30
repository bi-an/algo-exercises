// https://blog.csdn.net/MissXy_/article/details/93050545

#include <iostream>
#include <vector>
using namespace std;

#define MAX_INT 99997867 

int C(int n) {
	return (long long)n * (n - 1) / 2 % MAX_INT; // C(n,2)
}


// 滑动窗口，双指针调节
// 先固定最右边的一个人，再在符合距离要求的位置选择两个位置，即C(n,2)

int main() {
	int N, D;
	cin >> N >> D;
	vector<int> place;

	for (int i = 0; i < N; i++) {
		int tmp;
		cin >> tmp;
		place.push_back(tmp);
	}

	int ans = 0;
	for (int i = 2, j = 0; i < N; i++) {
		if (i - j >= 2) { // 必须要留三个及以上位置，因为有三个人
			while (place[i] - place[j] > D) {
				j++;
			}
			ans = ((long long)ans + C(i - j)) % MAX_INT; // 一定要防止溢出
		}
	}

	cout << ans;

	return 0;
}