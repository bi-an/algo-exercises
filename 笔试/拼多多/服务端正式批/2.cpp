#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(vector<int> &t1, vector<int> &t2) {
	return t1[0] < t2[0];
}

// 思路：
// 区间合并，对于区间[begin,end]的数组，先按照begin排序
// 然后合并

int main() {
	int N, M;
	cin >> N >> M; // N植树点，M小伙伴
	vector<int> ans;
	vector<vector<int> > num;
	for (int i = 0; i < M; i++) {
		int l, r;
		cin >> l >> r;
		vector<vector<int> > res; // 当前区间合并结果
		vector<int> tmp;
		tmp.push_back(l);
		tmp.push_back(r);
		num.push_back(tmp);
		sort(num.begin(), num.end(), comp); // 所有区间按照左边界排序
		res.push_back(num[0]);
		for (int j = 1; j < num.size(); j++) {
			vector<int>& cur = num[j];
			vector<int> &last = res[res.size()-1]; // last是当前res的最后一个区间
			if (cur[0] <= last[1]) { // 当前区间左边界位于last区间之中，应该合并区间
				last[1] = max(cur[1], last[1]);
			}
			else { // 当前区间与last区间不相交，并且当前区间位于last区间右边
				res.push_back(cur); // 把当前区间放入res的后面
			}
		}
		int sum = 0;
		for (vector<int> &cur:res) {
			sum += cur[1] - cur[0] + 1;
		}
		ans.push_back(sum);
		swap(num, res); // 保留本次区间合并的结果，极大地降低了时间复杂度
	}

	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << endl;
	}

	return 0;
}