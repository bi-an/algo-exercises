/*
最强大脑
时间限制：C/C++语言 1000MS；其他语言 3000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
人脑对于长度特别长的字符串的处理速度是有限的，但是最强大脑挑战的就是人脑的极限，现在有这样一项挑战，给出一个很长的字符串S，和一个较短的字符串T，请你求出对于每一个前缀[1,r]内有多少个T字符串。

输入
第一行一个字符串S。

第二行一个字符串T。两个字符串保证均只含小写字母。（1≤|S|≤500000, 1≤|T|≤100）

输出
输出仅包含|S|个正整数，分别表示[1,r]内有多少个T字符串。(1<=r<=|S|)


样例输入
ababac
ab
样例输出
0 1 1 2 2 2
*/


// 滑动窗口：
// 两个指针，闭区间[p1,p2]；窗口大小为字符串T的长度。

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string S, T;
	cin >> S >> T;
	vector<int> ans;
	int w = T.size();
	int p1 = 0, p2 = 0;
	int cnt = 0;
	for (int i = 0; i < S.size(); i++) {
		//if (i < w) {
		//	ans.push_back(0);
		//	continue;
		//}
		if (p2 - p1 + 1 >= w) {
			if (S.substr(p1, w) == T) {
				cnt++;
			}
			p1++; // 每次窗口大于w时，缩小至w大小
		}
		ans.push_back(cnt);
		p2++;
	}
	//ans.push_back(cnt);

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}

	return 0;
}