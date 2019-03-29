// 命令行读入字符串 空格分隔 换行结束

// 自己实现
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
	string str;
	getline(cin, str);
	
	vector<string> numbers;
	int p1 = str.find_first_not_of(" ");
	while (p1<str.size()) {
		string tmp;
		//while (p1<str.size() && str[p1] != ' ') {
		while (p1<str.size() && str[p1] >= '0' && str[i]<='9') {	
			tmp.push_back(str[p1]);
			p1++;
		}
		if (tmp.size() > 0)
			numbers.push_back(tmp);
		else
			p1++;
	}

	return 0;
}




// 推荐写法：getline

#include <iostream>
#include <string>
using namespace std;

int main() {
	string str;
	while (getline(cin, str, ' ')) { // geline指定分隔符
		if(!str.empty())
			printf("%s ", str.c_str());
	}

	return 0;
}
