/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
把n加数分解，使得所有加数之积最大

Example 1:
Input: 2
Output: 1
Explanation: 2 = 1 + 1, 1 × 1 = 1.

Example 2:
Input: 10
Output: 36
Explanation: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.

Note: You may assume that n is not less than 2 and not larger than 58.
*/


// 找规律
// 当f>=4, 2(f-2)>=f, 这说明如果含有一个因子f>=4, 那么这个因子还可以分解，分解结果能使得因子乘积增大，即因子一定小于等于3；
// 当n>=5, 3(n-3)>=2(n-2), 这说明当n>=5时，应该首先分解成3
// 当然推导时，是从右到左，因为不等式是等价关系。即由2(f-2)>=f，得到f>=4.
class Solution {
public:
    int integerBreak(int n) {
        if(n<=1) return 0;
        if(n==2)
            return 1;
        if(n==3)
            return 2;
        int product=1;
        while(n>=5){
            product*=3;
            n-=3;
        }
        while(n>=4){
            product*=2;
            n-=2;
        }
        if(n>0)
            product*=n;
        return product;
    }
};

// 动态规划
class Solution {
public:
    int integerBreak(int n) {
        if(n<=1) return 0;
        if(n==2) return 1;
        vector<int> dp(n+1,0); // 第一位不用, dp表示可能的最大积
        dp[1]=0, dp[2]=1; // 2=1+1, product_max=1*1=1
        for(int i=3;i<=n;i++){
            for(int j=1;j<=i/2;j++){
                dp[i]=std::max(dp[i],std::max(j*(i-j),j*dp[i-j]));
            }
        }
        return dp[n];
    }
};