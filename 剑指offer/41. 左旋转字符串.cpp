/*汇编语言中有一种移位指令叫做循环左移（ROL），
现在有个简单的任务，就是用字符串模拟这个指令的运算结果。
对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。
例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。*/

class Solution {
public:
	string LeftRotateString(string str, int n) {
		if (n == 0 || str.size()<=0) return str;
		int m = n;
		/*if (n < 0) m = -m;
		m %= str.length();
		if (n < 0) m = str.length() - m;*/
		string str1 = str.substr(0,m);
		string str2 = str.substr(m,str.length()-m);
		str1 = str2 + str1;
		return str1;
	}
};


// 解法2：利用翻转单词的原理
// 先将字符串分成两部分，分别翻转；然后再合并后，翻转整个字符串