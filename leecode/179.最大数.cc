#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
	string largestNumber(vector<int>& vec) {
		sort(vec.begin(), vec.end(), &Solution::cmp);
		string str;
		for (int i = 0; i < vec.size(); i++) {
			str += to_string(vec[i]);
		}
        if(str[0]=='0') return "0"; // 不能输出"00"
		return str;
	}

	static bool cmp(int a, int b) {
		string s1 = to_string(a), s2 = to_string(b);
		return s1 + s2 > s2 + s1;
	}
};