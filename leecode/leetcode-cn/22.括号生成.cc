// 递归
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        return helper(n);
    }

    vector<string> helper(int n){
        if(n == 0) return {""};
        vector<string> res;
        for(int i=0;i<n;i++){
            for(string& s : helper(i)){
                for(string& t : helper(n-i-1)) { // 由于本次消耗一个括号，所以-1
                    string str = "("+s+")"+t; // 可以自定义递归规则：所有的合法括号都可以分解成该式；递归本质：重复子结构
                    res.push_back(str);
                }
            }
        }
        return res;
    }
};