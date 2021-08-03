/**
 * 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

请你找出符合题意的 最短 子数组，并输出它的长度。

 
示例 1：

输入：nums = [2,6,4,8,10,9,15]
输出：5
解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
示例 2：

输入：nums = [1,2,3,4]
输出：0
示例 3：

输入：nums = [1]
输出：0
 

提示：

1 <= nums.length <= 104
-105 <= nums[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/shortest-unsorted-continuous-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */



// 方法一：排序
// 时间复杂度：O(nlogn)
// 空间复杂度：O(n)
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        vector<int> vec(nums);
        std::sort(vec.begin(), vec.end());
        int start = 0, end = nums.size();

        for(int i=nums.size()-1;i>=0;i--) {
            if(vec[i] == nums[i])
                end--;
            else
                break;
        }

        for(int i=0;i<end;i++) {
            if(vec[i] == nums[i])
                start++;
            else
                break;
        }

        return end - start;
    }
};


// 方法二：函数图象拐点
// 思路：画图象知，left是最左边的极大值点，right是最右边的极小值点
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int left = -1, right = -1, n = nums.size();
        int minn = INT_MAX, maxn = INT_MIN; // 这里是极值，不是真正的最大最小值
        
        // 这里其实是两趟遍历
        for(int i=0;i<n;i++) {
            // 从左到右遍历
            if(maxn > nums[i]) // 出现极大值点
                right = i; // 不断更新right，直至极小值点
            else
                maxn = nums[i];
            // 从右到左遍历
            if(minn < nums[n-1-i]) // 出现极小值点
                left = n-1-i; // 不断更新left，直至极大值点
            else
                minn = nums[n-1-i];
        }
        return left == -1 ? 0 : right - left + 1;
    }
};