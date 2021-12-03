class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int,int> freq; // 由于-100≤nums[i]≤100，可以用hashtable缩短排序时间

        int ans = accumulate(nums.begin(), nums.end(), 0);

        for(int i=0;i<n;i++)
            freq[nums[i]]++;

        for(int i=-100;i<0 && k > 0;i++) {
            if(freq[i]) {
                int ops = min(k, freq[i]);
                ans += (-i) * ops * 2;
                freq[i] -= ops; // 把负数转成正数过程中，可能出现了比原先的正数更小的数
                freq[-i] += ops;
                k-=ops;
            }
        }
        if(k > 0 && k % 2 == 1 && !freq[0]) {
            for(int i=1;i<=100;i++) {
                if(freq[i]) {
                    ans -= i*2;
                    break;
                }
            }
        }
        return ans;
    }
};