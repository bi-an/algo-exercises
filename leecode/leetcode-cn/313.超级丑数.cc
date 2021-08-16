// 本题与丑数II并无实际区别
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if(n <= 0) return 0;
        int m = primes.size();
        
        vector<int> ugly_numbers(n);
        ugly_numbers[0] = 1;
        vector<int> p(m, 0);

        for(int i=1;i<n;i++) {
            int min_val = INT_MAX;
            for(int j=0;j<m;j++) {
                if(primes[j] * ugly_numbers[p[j]] < min_val) {
                    min_val = primes[j] * ugly_numbers[p[j]];
                }
            }
            for(int j=0;j<m;j++) {
                if(primes[j] * ugly_numbers[p[j]] == min_val) {
                    p[j]++;
                }
            }
            ugly_numbers[i] = min_val;
        }

        return ugly_numbers[n-1];
    }
};