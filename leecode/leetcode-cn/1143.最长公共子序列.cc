#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<vector<int>> memo; // 备忘录：消除重复计算
public:
    int longestCommonSubsequence(string text1, string text2) {
        memo.resize(text1.size());
        for(int i=0;i<text1.size();i++)
            memo[i].resize(text2.size());
        for(int i=0;i<text1.size();i++)
            for(int j=0;j<text2.size();j++)
                memo[i][j]=-1;
        return dp(text1, 0, text2, 0);
    }
    int dp(string& text1, int i, string& text2, int j){
        if(i==text1.size() || j==text2.size())
            return 0;
        if(memo[i][j]!=-1)
            return memo[i][j];
        if(text1[i]==text2[j])
            memo[i][j] = dp(text1, i+1, text2, j+1) + 1;
        else
            memo[i][j] = max(dp(text1, i+1, text2, j), dp(text1, i, text2, j+1));
        return memo[i][j];
    }
};