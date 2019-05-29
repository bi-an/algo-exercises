class Solution {
public:
    int digitSquareSum(int n) {
        int sum = 0, tmp;
        while (n) {
            tmp = n % 10;
            sum += tmp * tmp;
            n /= 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        int slow, fast;
        slow = fast = n;
        do {
            slow = digitSquareSum(slow);
            fast = digitSquareSum(fast);
            fast = digitSquareSum(fast); // 如果平方和达到1，那么之后的平方和将一直是1
        } while(slow != fast); //  Floyd Cycle detection algorithm.
        if (slow == 1) return 1;
        else return 0;
    }
};