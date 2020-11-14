#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if(s.empty()) return true;
        stack<char> stk;
        for(int i=0;i<s.size();i++){
            if(isLeft(s[i]))
                stk.push(s[i]);
            else if(!stk.empty() && isMatch(stk.top(), s[i]))
                stk.pop();
            else
                return false;
        }
        return stk.empty();
    }

    bool isLeft(char c){
        return c=='(' || c=='[' || c=='{';
    }

    // a必须是左括号
    bool isMatch(char a, char b){
        if(a=='(') return b==')';
        if(a=='[') return b==']';
        if(a=='{') return b=='}';
        return false;
    }
};

int main() {
	Solution sol;
	bool res = sol.isValid("()");
    cout << res << endl;

	return 0;
}