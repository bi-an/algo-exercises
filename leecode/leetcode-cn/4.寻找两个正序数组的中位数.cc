/*
 * @Author: your name
 * @Date: 2021-09-04 12:38:37
 * @LastEditTime: 2021-09-04 12:39:56
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\leecode\leetcode-cn\4.寻找两个正序数组的中位数.cc
 */

// 双指针遍历
// 时间O(m+n)
// 空间O(1)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0, n1 = nums1.size(), n2 = nums2.size();
        int k = 0;
        int last = 0, cur = 0;
        double ans = 0;
        while(k++ <= (n1 + n2) / 2) {
            last = cur;
            if(i < n1 && j < n2) {
                if(nums1[i] < nums2[j]) {
                    cur = nums1[i++];
                } else {
                    cur = nums2[j++];
                }
            } else if(i < n1) {
                cur = nums1[i++];
            } else {
                cur = nums2[j++];
            }
        }
        if((n1 + n2) % 2 == 0) {
            ans = (last + cur) / 2.0;
        } else {
            ans = cur;
        }
        return ans;
    }
};

// 这是有序数组，可以二分查找
// 时间O(log(m+n))
// 空间O(1)
