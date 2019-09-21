#include <iostream>
#include <string>
using namespace std;

int compare(string version1, string version2) {
	version1 = version1 + ".";
	version2 = version2 + ".";
	int p1 = 0, p2 = 0;
	int pos1 = version1.find(".", 0);
	int pos2 = version2.find(".", 0);
	int diff = 0;
	while (pos1 != string::npos && pos2 != string::npos) {
		string str1 = version1.substr(p1, pos1 - p1);
		string str2 = version2.substr(p2, pos2 - p2);
		int v1 = atoi(str1.c_str());
		int v2 = atoi(str2.c_str());
		diff = v1 - v2;
		if (diff != 0)
			break;
		p1 = pos1 + 1; pos1 = version1.find(".", p1);
		p2 = pos2 + 1; pos2 = version2.find(".", p2);
	}
	if (diff > 0)
		return 1;
	else if (diff == 0)
		return 0;
	else
		return -1;
}

int main() {
	string version1, version2;
	cin >> version1 >> version2;
	int res = compare(version1, version2);
	cout << res << endl;

	return 0;
}