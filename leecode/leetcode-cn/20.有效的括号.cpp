// #include <bits/stdc++.h>
// using namespace std;

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

// 写法二
class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> mypair = {
            {'(', ')'}, {'{', '}'}, {'[', ']'}
        };
        stack<char> mystack;
        for (char c : s) {
            if (c == '(' || c == '{' || c == '[') {
                mystack.push(c);
            }
            else {
                if (mystack.empty() || mypair[mystack.top()] != c)
                    return false;
                mystack.pop();
            }
        }
        return mystack.empty();
    }
};