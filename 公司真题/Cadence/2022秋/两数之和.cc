// 姻缘配
// 从输入的数字中，找出两个相加之和为 m 的两个数。计算这样的匹配对的个数。
// 不同下标的数视为不同，即使它们数值上相等。

#include <bits/stdc++.h>
using namespace std;

int main() {
	int m, N;
	cin >> m >> N;
	vector<int> nums(N);
	map<int, int> cnt;
	for (int i = 0; i < N; ++i) {
		cin >> nums[i];
		++cnt[nums[i]];
	}
	sort(nums.begin(), nums.end()); // 为了去重
	long ans = 0;
	int last = -1;
	for (int i = 0; i < N; ++i) {
		int x = nums[i];
        // 去重
		if (x > m / 2)
			break;
		if (x == last)
			continue;
		int y = m - x;
		if (x == y) {
			if (cnt[x] > 1)
				ans += (long)cnt[x] * (cnt[x] - 1) / 2;
		}
		else {
			ans += (long)cnt[x] * cnt[y];
		}
		last = x;
	}
	cout << ans << endl;

	return 0;
}


// 方法二：去重不需要排序。
long long countSum(vector<int>& nums, int m) {
    long long ans = 0;

    map<int, int> cnt;
    for (int x : nums) {
        ++cnt[x];
    }

    for (int x : nums) {
        int y = m - x;
        // 去重
        if (y > x || !cnt.count(y))
            continue;
        if (x == y) {
            ans += (long long)cnt[x] * (cnt[x] - 1) / 2;
        } else {
            ans += (long long)cnt[x] * cnt[y];
        }
    }

    return ans;
}
