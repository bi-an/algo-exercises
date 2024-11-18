class Solution {
public:
    int findMinFibonacciNumbers(int k) {
        vector<int> tmp;
        int first = 1, second = 1, third;
        tmp.push_back(first);
        tmp.push_back(second);
        while(second <= k) {
            third = first + second;
            tmp.push_back(third);
            first = second;
            second = third;
        }
        int n = tmp.size();
        int cnt = 0;
        for(int i=n-1;i>=0 && k > 0;i--) {
            if(k - tmp[i] >= 0) {
                k -= tmp[i];
                cnt++;
            }
        }
        return cnt;
    }
};