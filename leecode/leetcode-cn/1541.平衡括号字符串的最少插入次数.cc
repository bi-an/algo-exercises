#include <bits/stdc++.h>
using namespace std;

/**
 * @file 1541.平衡括号字符串的最少插入次数.cc
 * @date 2020-11-14
 * @ref labulangdong
 * 
 * 如果不及时将右括号数放入res暂存，则在今后遇到右括号时慢慢被减去时，need会慢一步到达-1，
 * 因为到达-1意味着结果陡增（left+1, right+2），而慢一步达到-1，则结果反而减少了1，
 * 导致最终所需要的括号总数变少（少了3）。例如：
 *              )   (   )   (   )   )       )
 * need     -1->1   3   2   3   2   1       0
 * res       0->1   1   1   2   2   2       2
 *                                
 * 实际如下
 *          
 * need     -1->1   2   1   2   1   0   -1->1
 * res       0->1   2   2   3   3   3    2->4
 */

class Solution {
public:
    int minInsertions(string s) {
        // need为此后需要的右括号
        // res为暂存区，可能同时包括'('和')'
        int res = 0, need = 0; 
        
        for(int i=0;i<s.size();i++){
            if(s[i]=='('){
                need+=2;
                if((need&1)==1){
                    res++; // 暂存（保证所需的右括号数不会变少）
                    need--; // 本处左括号，之后的右括号数应该为偶数
                }
            }
            else if(s[i]==')'){
                need--;
                if(need==-1){
                    res++; // 需要一个左括号
                    need=1; // 还差一个右括号
                }
            }
        }

        return res+need;
    }
};