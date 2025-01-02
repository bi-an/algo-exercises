class Solution {
public:
    vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
        int n = increase.size(), m = requirements.size();

        vector<int> C(n + 1), R(n + 1), H(n + 1);
        for (int i = 1; i <= n; ++i) {
            auto& a = increase[i - 1];
            C[i] += C[i - 1] + a[0];
            R[i] += R[i - 1] + a[1];
            H[i] += H[i - 1] + a[2];
        }

        vector<int> ans(m);
        int t = 0;
        for (auto& r : requirements) {
            int i = ranges::lower_bound(C, r[0]) - C.begin();
            int j = ranges::lower_bound(R, r[1]) - R.begin();
            int k = ranges::lower_bound(H, r[2]) - H.begin();
            int day = ranges::max({i, j, k});
            ans[t++] = day == n + 1 ? -1 : day;
        }
        return ans;
    }
};

namespace version_2 {

// 写法二：不需要额外空间
// 由于我们没有使用前缀和，所以有个易错点：
// 如果在 requirements 全为 0 ，那么在 increase 之前就满足，此时应该返回第 0 天（而不是第 1 天）。
class Solution {
public:
    vector<int> getTriggerTime(vector<vector<int>>& increase, vector<vector<int>>& requirements) {
        int n = increase.size(), m = requirements.size();

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < 3; ++j)
                increase[i][j] += increase[i - 1][j];
        }

        vector<int> ans(m);
        int t = 0;
        for (auto& r : requirements) {
            // 特殊处理易错点
            // 也可以在 increase 前面插入一个元素 {0,0,0} ，就变成前缀和了
            // if (r == vector<int>({0, 0, 0})) {
            if (r[0] == 0 && r[1] == 0 && r[2] == 0) {
                ans[t++] = 0;
                continue;
            }
            // 注意这个 comparison 判定条件
            int i = ranges::lower_bound(increase, r, [](auto& a, auto& b) {
                        return a[0] < b[0] || a[1] < b[1] || a[2] < b[2];
                    }) -
                    increase.begin();

            ans[t++] = i == n ? -1 : i + 1;
        }
        return ans;
    }
};

}  // namespace version_2
