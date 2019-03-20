/*
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，
打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，
则打印出这三个数字能排成的最小数字为321323。
*/

class Solution {
public:
	string PrintMinNumber(vector<int> numbers) {
		string res;
		//if (numbers.empty()) return res;

		sort(numbers.begin(),numbers.end(),compare);// compare为函数地址
		for (size_t i = 0; i < numbers.size(); i++) {
			res += to_string(numbers[i]);
		}
		return res;
	}

//注意： 因为在类的实例没有初始化时，其成员函数没有地址，因此如果这样写的话，必须把比较函数声明为静态，或者写在类外面。
	static bool compare(int a, int b) {
		string str1 = to_string(a);
		string str2 = to_string(b);
		return (str1+str2) < (str2+str1);
	}
};

