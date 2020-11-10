#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 参考labuladong
 * 
 * dp(i,j) 表示子串s1[i...n-1]与子串s2[j...m-1]的最长公共子串长度
 * 那么，我们需要求dp(0,0)
 * 
 * 递归结束条件：
 *      if(i==n || j==m)
 *          return 0; // 因为s1[i...n-1]或s2[j...m-1]其中一个长度为0，当然公共子串长度为0
 * 
 *  1. 如果s1[i]==s2[j]
 *      dp(i,j) = dp(i+1,j+1)+1
 *  2. 如果s1[i]!=s2[j]
 *      2.1 如果s1[i]==s2[j+1]
 *          dp(i,j) = dp(i,j+1)
 *      2.2 如果s1[i+1]==s2[j]
 *          dp(i,j) = dp(i+1,j)
 *      2.3 其他情况被2.1和2.2囊括了
 * 其实，第2种情况不需要判断s1[i]和s2[j+1]这些相等情况，直接求他们之间的max就可以了
 * 因为是否相等可以在下一次递归时，将由第1种情况来判断
 */
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