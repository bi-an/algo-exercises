class Solution {
    static constexpr int MOD = 1000000007;
public:
    int kInversePairs(int n, int k) {
        vector<int> pre(k + 1, 0), cur(k + 1, 0);
        cur[0] = 1;
        for (int i = 2; i <= n; i++) {
            pre[0] = 1, cur[0] = 1;
            for (int j = 1; j <= k; j++) {
                cur[j] = ((long)cur[j - 1] - (j < i ? 0 : pre[j - i]) + pre[j]);
                if(cur[j] > MOD)
                    cur[j] -= MOD;
                if(cur[j] < 0)
                    cur[j] += MOD; // TODO 为啥不是设为0？
            }
            pre = cur;
        }
        return cur[k];
    }
};