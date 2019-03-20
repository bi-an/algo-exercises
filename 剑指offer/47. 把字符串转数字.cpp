class Solution {
public
	int StrToInt(string str) {
		if (str.empty()) return 0;

		size_t start = 0;
		int flag = 1;
		if (str[0] == '+'  str[0] == '-') {
			start = 1;
			if (str[0] == '-')
				flag = -1;
		}

		if (start == str.length()) return 0;

		int res = 0;
		for (size_t i = start; i  str.length();i++) {
			int num = str[i] - '0';
			if (num  9  num  0) {
				return 0;
			}
			res = res  10 + num;
		}

		return flag  res;

	}
};