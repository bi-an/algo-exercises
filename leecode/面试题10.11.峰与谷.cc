#include <vector>
#include <algorithm>
using namespace std;

/**
 * 要求峰-谷-峰-谷的排序，即
 * 索引：0 > 1 < 2 > 3 < 4 > 5
 * 从奇数索引看：(0 > 1) < (2 > 3) < (4 > 5)
 * 会发现，全是大于号；如果a>b>c，由于传递性，a>c，那么交换b和c即可，有a>c<b
 */

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        for(int i=1;i<nums.size();i++){
            if((i&1)==1){ // 奇数索引
                if(nums[i]<nums[i-1])
                    swap(nums[i],nums[i-1]);
            }
            else{
                if(nums[i]>nums[i-1])
                    swap(nums[i],nums[i-1]);
            }
        }
    }
};