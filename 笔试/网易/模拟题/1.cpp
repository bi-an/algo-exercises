// 计算个人所得税
// 5000以下不交税，5000以上部分按照区间交税。
// 输出结果四舍五入成整数

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double fee(double x) {
	x -= 5000; 
	if (x <= 0)
		return 0;
	double base[7] = {3000, 12000-3000, 25000-12000, 35000-25000, 55000-35000, 80000-55000, 0};
	double rate[7] = { 0.03, 0.1, 0.2, 0.25,0.3,0.35,0.45 };
	int last = x;
	for (int i = 0; i < 7; i++) {
		last = x;
		x -= base[i];
		if (x < 0 && last > 0) {
			base[i] = last;
			for(int j=i+1;j<7;j++)
				base[j] = 0;
			break;
		}
	}
	if (x > 0)
		base[6] = x;
	double sum = 0;
	for (int i = 0; i < 7; i++) {
		sum += base[i] * rate[i];
	}
	return sum;
}

int main() {
	std::vector<int> input;
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int temp;
		cin >> temp;
		input.push_back(temp);			
	}
	
	for (int i = 0; i < N; i++) {
		std::cout << round(fee(input[i])) << std::endl;
	}

	return 0;
}