/**
峰值元素是指其值严格大于左右相邻值的元素。

给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞ 。

你必须实现时间复杂度为 O(log n) 的算法来解决此问题。

 

示例 1：

输入：nums = [1,2,3,1]
输出：2
解释：3 是峰值元素，你的函数应该返回其索引 2。
示例 2：

输入：nums = [1,2,1,3,5,6,4]
输出：1 或 5 
解释：你的函数可以返回索引 1，其峰值元素为 2；
     或者返回索引 5， 其峰值元素为 6。
 

提示：

1 <= nums.length <= 1000
-2^31 <= nums[i] <= 2^31 - 1
对于所有有效的 i 都有 nums[i] != nums[i + 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-peak-element
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

// 法一：由题意，最大值一定是峰值
// 时间复杂度O(n)，不符合要求
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        auto itr = std::max_element(nums.begin(),.end()); // ForwardIterator
        return itr - nums.begin();
    }
};


// 法二：二分查找，局部爬坡
// 只要注意判断middle爬坡方向是左还是右即可
// 时间复杂度O(logn)
// 二分法的本质不是有序，而是不断压缩范围以找到答案
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = int(nums.size()) - 1, middle = 0;
        while(left <= right) {
            middle = (left + right) / 2; // middle靠左
            if(middle + 1 < nums.size() && nums[middle+1] > nums[middle]) {
                left = middle + 1; // 往右爬坡
            } else if(middle - 1 >= 0 && nums[middle-1] > nums[middle]) {
                right = middle - 1; // 往左爬坡
            } else {
                // 边界情况只有两种：
                // (1) 区间剩余1个元素，此时left、middle、right相同：
                // 返回left、middle、right都可。
                // (2) 区间剩余2个元素，此时left与middle相同，right比left大1：
                // 此时应该返回 middle 和 middle + 1 中所指元素更大的。
                // 经过第一个if排除，可以得出：nums[middle+1] <= nums[middle]；
                // 而第二个if条件显然不满足 middle -1 >= 0；
                // 故，情况(2)只可能是nums[middle+1] <= nums[middle]，返回middle.
                return middle;
            }
        }
        return left;
    }
};
