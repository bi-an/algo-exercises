#include <bits/stdc++.h>

class Solution {
public:
    int minAddToMakeValid(string S) {
        if(S.empty()) return 0;
        int need = 0, res = 0;
        for(int i=0;i<S.size();i++){
            if(S[i]=='('){
                need++;
            }
            else if(S[i]==')'){
                need--;
                // 表明此时是多了一个右括号
                if(need==-1){
                    res++; // 需要一个左括号
                    need = 0;
                }
            }
        }
        return res+need;
    }
};