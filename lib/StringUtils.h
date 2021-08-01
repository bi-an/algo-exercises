/*
 * @Author: your name
 * @Date: 2021-08-01 20:28:24
 * @LastEditTime: 2021-08-01 23:49:38
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\lib\String.h
 */

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <string>

using std::string;
using std::vector;

// 提供string相关的static函数
class StringUtils {
public:
	static vector<string> split(string str, const char c) {
		vector<string> ans;

		str += c;
		int begin = 0, end = 0;
		while (end < str.size()) {
			if (str[end] != c) {
				end++;
				continue;
			}
			string cur = str.substr(begin, end - begin);
			ans.push_back(cur);
			begin = ++end;
		}

		return ans;
	}

	static string& trim(string& str) {
		int begin = str.find_first_not_of(' ');
		int end = str.find_last_not_of(' ');
		if (begin == end) {
			str.clear();
			return str;
		}
		str = str.substr(begin, end - begin + 1);
		return str;
	}

	static char* trim(char* str) {
		if (str == nullptr) return nullptr;
		int r = -1, w = 0, n = strlen(str); // 读指针和写指针
		while (++r < n && str[r] == ' ') {} // 找到第一个不为空的位置
		while (r < n) {
			str[w++] = str[r++];
		}
		str[w] = '\0'; // 注意: 这种方式不能截断std::string
		while (--w >= 0 && str[w] == ' ') {
			str[w] = '\0';
		} // 回退写指针到倒数第一个不为空的位置
		return str;
	}
};

#endif