#include <iostream>
using namespace std;

// 第一天吃s块, 能吃的最大天数
int maxDays(int s, int M) {
	int sum = s, days = 1;
	while (s >= 1 && sum < M) {
		s = (s + 1) / 2; // 向上取整，如果s=1，那么之后每天都是1
		sum += s;
		days++;
	}
	return days;
}

int main() {
	int N, M;
	//N = 3, M = 7;
	cin >> N >> M;

	int res = 0;
	// 二分查找，降低时间复杂度
	int left = 1, right = M;
	while (left <= right) {
		int mid = (left + right) / 2;
		int max = maxDays(mid, M);
		if (max == N) {
			//res = mid;
			break;
		}
		else if (max < N) {
			right = mid - 1;
		}
		else
			left = mid + 1;
	}

	// 假设退出while之前，left=4,right=4 => mid=(left+right)/2=4, 此时max<N,则right=mid-1=3, 退出循环
	// 此时left=4,right=3,res=(left+right)/2=3
	// 由于之前left=4,right=4,故之前left一定是因为max>N，才有left=mid+1,不然left一直是1，故这个left=mid+1=>mid=3，这个mid是满足max>N的，
	// 所以res=3是满足题意的。

	// 还有一种情况是left一直都等于1，right一直再向左移，而退出之前，max==N一直都没有达到，所以，此时是没有答案的，
	// 退出循环时，left=1,right=0, 所以res=0，也是满足题意的。
	res = (left + right) / 2;
	cout << res;

	return 0;
}