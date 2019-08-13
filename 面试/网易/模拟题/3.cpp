// 题目：
// 一个数的X进制和Y进制表示连在一起（忘记打印空格），求这个数的十进制数大小。
// 题目保证一定有唯一解，0 < X,Y < 16, 超出10的部分分别用A,B,...,F表示。
// 输入: X, Y, 连在一起的表示，如 5 2 123411000010
// 输出: 这个数的十进制数大小，上面输入的答案是194

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// 把其他进制的数转化成10进制
int getDec(std::string str, int N) {
	int res = 0;
	if (str.empty())
		return -1;
	for (int i = str.size() - 1; i >= 0; i--) {
		int factor = pow(N, str.size() - 1 - i);
		int num = str[i] - '0';
		if (num >= 10 && N <= 10) {
			return -1;
		}
		if (num >= 10) {
			num = str[i] - 'A' + 10;
		}
		res += factor * num;
	}
	return res;
}

// 从中间开始找，如果转化成10进制之后，两者不等，就把中间位置div朝着N和M中较大的一方移动，直至两者相等
int getRes(std::string str, int N, int M) {
	int res = 0;
	int div = str.size() / 2;
	int flag = 1;
	if (N > M) {
		flag = -1;
	}
	while ((res = getDec(str.substr(0, div), N)) != getDec(str.substr(div, str.size() - div), M) && div!=str.size()) {
		div+=flag;
	}
	return res;
}

int main() {
	vector<int> res;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int N, M;
		cin >> N >> M;
		getchar();
		string temp;
		getline(cin, temp);
		/*std::cout << temp << std::endl;*/
		res.push_back(getRes(temp, N, M));
	}

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i] << std::endl;
	}

	return 0;
}


// 附加：
// 把十进制数转化成N进制
std::string dec2N(int num, int N) {
	std::string res;
	while (num > 0) {
		int m = num % N;
		num /= N;
		// res = std::to_string(m) + res;
		string bit;
		if (m >= 10)
			bit = m - 10 + 'A';
		else
			bit = m + '0';
		res = bit + res;
	}
	return res;
}