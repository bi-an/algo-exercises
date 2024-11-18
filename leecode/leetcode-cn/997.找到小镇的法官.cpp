class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) {
        // 有向图的出度和入度
        vector<int> inDegrees(n + 1);
        vector<int> outDegrees(n + 1);

        for (vector<int>& p : trust) {
            outDegrees[p[0]]++;
            inDegrees[p[1]]++;
        }

        int ans = -1;
        for (int i = 1; i <= n; i++) {
            if (inDegrees[i] == n - 1 && outDegrees[i] == 0) {
                ans = i;
                break;
            }
        }

        return ans;
    }
};