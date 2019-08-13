作者：你今天刷题了吗
链接：https://www.nowcoder.com/discuss/221051
来源：牛客网

#include<bits/stdc++.h>
using namespace std;

int main() {
 int T, m, t, m1, m2, t1, t2;
 scanf("%d", &T);
 while (T--) {
  scanf("%d %d %d %d %d %d", &m, &t, &m1, &t1, &m2, &t2);
  int res = 0;
  for (int i = 0; i < t; i++) {
   if (i / t1 % 2 == 0)res += m1;
   if (i / t2 % 2 == 0)res -= m2;
   if (res < 0)res = 0;
   else if (res > m)res = m;
  }
  printf("%d\n", res);
 }
 return 0;
}



int main(){
	int t;
	cin >> t;
	while (t--){
		vector<int> a(6);
		int m, t, m1, t1, m2, t2;
		cin >> m >> t >> m1 >> t1 >> m2 >> t2;
		int flag1 = 1, flag2 = 1,sum=0;
		for (int i = 1, j = 1; i <= t && j <= t; i++, j++){
			if (flag1 == 1 && sum <= m){
				sum += m1;
				if (sum >=m) sum = m;
			}
			if (flag2 == 1 && sum >0){
				sum -= m2;
				if (sum <= 0) sum = 0;
			}
			if (i%t1 == 0)
				flag1 ^= 1;
			if (j%t2 == 0)
				flag2 ^= 1;
		}
		cout << sum << " ";
	}
	
	system("pause");
	return 0;
}



// @Athor zzg
#include <iostream>
#include <vector>
using namespace std;

int waterLeft(int m, int t, int m1, int t1, int m2, int t2) {
	int water = 0;
	bool f1 = 0, f2 = 0;
	for (int i = 0; i < t; i++) {
		if (i%t1 == 0)
			f1 = !f1;
		if (i%t2 == 0)
			f2 = !f2;
		int w = water + f1 * m1 - f2 * m2;
		if (w > m)
			water = m;
		else if (w <= 0)
			water = 0;
		else
			water = w;
	}
	return water;
}

int main() {
	int T;
	cin >> T;
	vector<int> ans(T, 0); // 提前分配vector，并初始化为0
	for (int i = 0; i < T; i++) {
		int m, t, m1, t1, m2, t2;
		cin >> m>> t>> m1>> t1>> m2>> t2;
		//ans.push_back(waterLeft(m, t, m1, t1, m2, t2));
		ans[i] = waterLeft(m, t, m1, t1, m2, t2);
	}
	for (int i = 0; i < T; i++) {
		std::cout << ans[i] << std::endl;
	}

	return 0;
}