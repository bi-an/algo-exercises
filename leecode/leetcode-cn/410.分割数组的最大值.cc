#include <vector>
using namespace std;

// 本题使用二分查找优化效率
class Solution {
public:
    int splitArray(vector<int>& nums, int m) {
        int lo = getMax(nums), hi = getSum(nums);
        while(lo <= hi){
            int mid = (lo + hi) / 2;
            int n = split(nums, mid);
            if(n==m)
                hi = mid - 1;
            else if(n>m) // n必须多分组，说明此时的sum过小
                lo = mid + 1;
            else if(n<m)
                hi = mid - 1;
        }
        return lo;
    }

    int getMax(vector<int>& nums){
        int max_val = nums[0];
        for(int i=1;i<nums.size();i++) {
            if(max_val < nums[i])
                max_val = nums[i];
        }
        return max_val;
    }
    int getSum(vector<int>& nums){
        int sum = 0;
        for(int i=0;i<nums.size();i++) {
            sum+=nums[i];
        }
        return sum;
    }
    // @return int 当连续子数组和最大为maxSum时，至少可以分割的子数组个数
    int split(vector<int>& nums, int maxSum){
        int n = 1;
        int sum = 0;
        for(int i=0;i<nums.size();i++){
            if(sum+nums[i] > maxSum){ // 该组不能再添加了
                n++;
                sum = nums[i];
            }
            else{
                sum += nums[i];
            }
        }
        return n;
    }
};