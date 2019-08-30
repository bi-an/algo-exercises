#include <iostream>
using namespace std;

int main(){
	long n,m; // 注意，这里要用long，用int会越界
	cin >> n >> m;

	long res = n*m/2;

	cout << res;

	return 0;
}