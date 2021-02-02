#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

static int count = 0;

static void printIndent(int n) {
    for (int i = 0; i < n; i++)
        printf("  ");
}

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        memo.resize(ring.size());
        for (int i = 0; i < ring.size(); i++) {
            charToIndex[ring[i]].push_back(i);
            memo[i].resize(key.size());
        }

        return dp(ring, 0, key, 0);
    }

    int dp(string ring, int i, string key, int j) {
        //printIndent(::count++);
        //printf("i = %d, j = %d\n", i, j);

        if (j == key.size()) {
            //printIndent(--::count);
            //printf("return 0\n");
            return 0;
        }
        if (memo[i][j] != 0)
            return memo[i][j];
        int n = ring.size();
        int res = INT_MAX;
        for (int k : charToIndex[key[j]]) {
            int delta = abs(k - i);
            delta = min(delta, n - delta);
            // +1是因为按下中心按钮也是一次操作
            res = min(res, 1 + delta + dp(ring, k, key, j + 1));
        }
        memo[i][j] = res;

        //printIndent(--::count);
        //printf("return %d\n", res);
        return res;
    }

private:
    map<char, vector<int>> charToIndex;
    vector<vector<int>> memo;
};

int main() {
    Solution sol;
    string ring = "godding", key = "gd";
    int ans = sol.findRotateSteps(ring, key);
    
	cout << endl << ans << endl;

	return 0;
}