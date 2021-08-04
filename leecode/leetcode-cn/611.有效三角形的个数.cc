/*
 * @Author: your name
 * @Date: 2021-08-05 01:00:49
 * @LastEditTime: 2021-08-05 01:06:24
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\611.有效三角形的个数.cc
 */

/**
给定一个包含非负整数的数组，你的任务是统计其中可以组成三角形三条边的三元组个数。

示例 1:

输入: [2,2,3,4]
输出: 3
解释:
有效的组合是: 
2,3,4 (使用第一个 2)
2,3,4 (使用第二个 2)
2,2,3
注意:

数组长度不超过1000。
数组里整数的范围为 [0, 1000]。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-triangle-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 *
 */

// 方法一：排序+二次遍历*一次二分查找
// 先排序
// 遍历nums[i]和nums[j]，然后在j+1...n-1中查找nums[k]，此时可以通过二分查找，找到恰好等于或者最后一个小于nums[i]+nums[j]的位置
// 时间复杂度：O(n^2*logn)，由题意nums.length为10^3，那么此复杂度不会超过10^8，是可以的。
// 空间复杂度：O(1)
class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        int ans = 0, n = nums.size();
        for(int i = 0;i<n;i++) {
            for(int j = i+1; j < n; j++) {
                int sum = nums[i] + nums[j];
                int left = j+1, right = n - 1;
                while(left <= right) {
                    int mid = (left + right) / 2;
                    if(nums[mid] >= sum) {
                        right = mid - 1;
                    } else {
                        left = mid + 1;
                    }
                }
                ans += left - j - 1;
            }
        }
        return ans;
    }
};
