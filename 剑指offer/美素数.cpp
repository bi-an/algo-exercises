#include <iostream>	
#include <sstream>
#include <fstream>
#include <sstream>
#include <cmath>

bool isPrime(int num) {
	if (num <= 0) {
		return false;
	}
	if (num%2==0)
		return false;
	if (num == 1 )
		return true;
	for (size_t i = 2; i*i <= num; i++) {
		if (num%i == 0) {
			return false;
			//break;
		}
	}
	return true;
}

int main() {
	std::ifstream fin("execute.stdin");
	std::string str;
	getline(fin,str);

	size_t index=str.find(" ",0);
	int L = atoi(str.substr(0,index+1).c_str());
	int R = atoi(str.substr(index+1,str.end()-str.begin()).c_str());
	int summary = 0;

	for (size_t i = L; i <= R;i++) {
		int num = i;
		int	sum = 0;
		if (isPrime(num)) {
			int m = num/10;
			int r = num%10;
			sum = sum + r;
			while (m > 0) {
				r = m % 10;
				m = m / 10;
				sum = sum + r;
			}
			if (isPrime(sum)) {
				summary++;
			}
		}
	}
	std::cout << summary << std::endl;
	return 0;
}