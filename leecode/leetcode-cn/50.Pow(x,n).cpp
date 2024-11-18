// 快速幂算法
// 时间复杂度：O(log(n))

// 递归写法
class Solution {
public:
    double myPow(double x, int n) {
        double ans = n > 0 ? myPow2(x, n) : myPow2(x, -(long long)n);
        return n > 0 ? ans : 1.0/ans;
    }

    double myPow2(double x, long long n) {
        if(n == 0)
            return 1;
        
        double y = myPow2(x, n/2);
        return n % 2 == 1 ? x * y * y : y * y;
    }
};

// 迭代写法
// 迭代写法不是那么直观，见 md 文件说明。
class Solution {
public:
    double myPow(double x, int n) {
        double ans = quickMul(x, n > 0 ? n : -(long long)n);
        return n > 0 ? ans : 1.0/ans;
    }

    double quickMul(double x, long long n) {
        double w = x; // weight
        double ans = 1;

        while(n) {
            if(n & 1) {
                ans *= w;
            } /* else {
                ans *= 1;
            } */
            w *= w; // w不断平方
            n >>= 1; // n不断右移
        }
        return ans;
    }
};