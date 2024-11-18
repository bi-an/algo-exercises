// 法一：保存进位
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ans(n);
        int carry = 0;
        digits[n-1]++;
        for(int i=n-1;i>=0;i--) {
            ans[i] = (digits[i] + carry) % 10;
            carry = (digits[i] + carry) / 10;
        }
        
        if(carry > 0) {
            vector<int> ans1(n + 1);
            ans1[0] = carry;
            for(int i=1;i<n+1;i++) {
                ans1[i] = ans[i-1];
            }
            ans.swap(ans1);
        }
        return ans;
    }
};

// 找规律
// 从右往左找到第一个不为9的数字，将其加1，并且把其右边所有的9改成0即可
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        for(int i = n - 1; i >= 0; i--) {
            if(digits[i] == 9) {
                digits[i] = 0;
            } else {
                digits[i]++;
                return digits;
            }
        }
        // 所有位都为9
        vector<int> ans(n + 1, 0);
        ans[0] = 1;
        return ans;
    }
};