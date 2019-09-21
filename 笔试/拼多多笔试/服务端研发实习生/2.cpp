/*
2 纸箱收纳 
 
题目描述 
小多有 N 个空纸箱，每个纸箱是一个边长为 Ai 的正方体。第 i 个纸箱可以装进第 j 个
纸箱里当且仅当以下 3 个条件同时满足： 
1. 纸箱 j 中没有装其他纸箱 
2. 纸箱 i 没有被装到其他纸箱中 
3. 纸箱 i 的边长小于纸箱 j，即 Ai < Aj。 
现在小多希望将一些纸箱装进其他纸箱中，使得肉眼可见的纸箱个数最少(被装到纸箱
里的纸箱肉眼不可见)。 
 
输入格式 
第一行包含一个正整数 N，表示纸箱个数。 
第二行包含 N 个正整数 Ai，分别表示每个纸箱的边长。 
数据范围： 
1 <= N <= 100000 
1 <= Ai <= 1000000000 
 
输出格式 
输出一行，包含一个整数，表示肉眼可见的最少纸箱个数。 
 
示例 1 
输入
5 
3 2 4 1 4 

输出
2 

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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