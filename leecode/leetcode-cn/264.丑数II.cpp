class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> uglyNumbers(n);
        uglyNumbers[0] = 1;
        int p2 = 0, p3 = 0, p5 = 0;

        for (int i = 1; i < n; i++) {
            int candidate2 = 2 * uglyNumbers[p2];
            int candidate3 = 3 * uglyNumbers[p3];
            int candidate5 = 5 * uglyNumbers[p5];
            int next = min(min(candidate2, candidate3), candidate5);
            if (candidate2 == next)
                p2++;
            if (candidate3 == next) // 不能使用else if，因为candidates之间可能恰好相同
                p3++;
            if (candidate5 == next)
                p5++;
            //cout << next << " ";
            uglyNumbers[i] = next;
        }
        //cout << endl;
        return uglyNumbers[n - 1];
    }
};