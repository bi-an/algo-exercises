#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 纸箱收纳

// 思路：只要是不同大小的纸箱子，就能全部收纳成一个纸箱；
// 所以，题目就变成：找出相同纸箱子的最大个数
int pack(vector<int>& vec) {
	if (vec.empty()) return 0;
	std::sort(vec.begin(), vec.end());
	int maxSame = 1, curSame = 1;
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i] != vec[i - 1]) {
			if (curSame > maxSame)
				maxSame = curSame;
			curSame = 1;
		}
		else {
			curSame++;
		}
	}
	if (curSame > maxSame)
		maxSame = curSame;
	return maxSame;
}

int main() {
	int N;
	vector<int> vec;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		vec.push_back(temp);
	}
	int res = pack(vec);
	cout << res << endl;
	return 0;
}