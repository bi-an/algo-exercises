/*
 * @Author: your name
 * @Date: 2021-09-04 12:38:37
 * @LastEditTime: 2022-07-03 16:26:58
 * @LastEditors: bi_an:desktop 2608120872@qq.com
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
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if ((n1 + n2) % 2 == 0) {
            return (getKthNum(nums1, nums2, (n1 + n2)/ 2) 
                + getKthNum(nums1, nums2, (n1 + n2) / 2 + 1)) / 2.0;
        } else {
            return getKthNum(nums1, nums2, (n1 + n2) / 2 + 1);
        }
    }

    int getKthNum(vector<int>& nums1, vector<int>& nums2, int k) {
        int i = 0, j = 0, n1 = nums1.size(), n2 = nums2.size();
        if (k > n1 + n2)
            return -1;
        while (k > 1) {
            int delta = k / 2 - 1;
            if (i + delta < n1 && j + delta < n2) {
                if (nums1[i + delta] < nums2[j + delta]) {
                    i += delta + 1;
                } else {
                    j += delta + 1;
                }
            } else if (i + delta < n1) {
                i += delta + 1;
            } else if (j + delta < n2) {
                j += delta + 1;
            }
            k -= k/2;
        }
        if (i < n1 && j < n2) {
            return min(nums1[i], nums2[j]);
        } else if (i < n1) {
            return nums1[i];
        }
        return nums2[j];
    }
};

// 方法三：划分数组
// 时间复杂度：O(log min(m, n))
// 空间复杂度：O(1)
// @ref 官方题解
// TODO