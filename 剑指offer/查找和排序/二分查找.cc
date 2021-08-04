/*
 * @Author: your name
 * @Date: 2020-10-23 21:24:25
 * @LastEditTime: 2021-08-05 00:59:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \practice\剑指offer\查找和排序\二分查找.cc
 */
#include <iostream>
using namespace std;

int biSearch(int nums[], int n, int val){
    if(nums==nullptr || n <= 0)
        return -1;
    
    int left = 0, right = n-1, mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(nums[mid] == val)
            return mid;
        else if(nums[mid] < val)
            left = mid + 1;
        else if(nums[mid] > val)
            right = mid - 1;
    }
    return -1;
}

/**
 * 思路：
 * 1. k存在：
 * 当nums[mid]>=k，继续二分查找，此时right将左移，left将右移，可以肯定的是，
 * left必然在k的左边或者恰好指向第一个k，而且最终left会恰好指向第一个k或者第一个k的前一位
 * 而right最终必然指向第一个k。
 * （1）left指向第一个k的前一位：
 *       right
 *         ↓
 *       3 5 5 5 5 5 7
 *       ↑
 *      left
 *  下一步left=mid+1，但是还没有完，
 *       right
 *         ↓
 *       3 5 5 5 5 5 7
 *         ↑
 *        left
 *  此时left==right，循环继续，right=mid+1
 *    right
 *       ↓
 *       3 5 5 5 5 5 7
 *         ↑
 *        left
 *  答案为left。
 * （2）left恰好指向第一个k：
 *       right
 *         ↓
 *       3 5 5 5 5 5 7
 *         ↑
 *       left
 *  此时right最终也会指向第一个k，下一步，right=mid-1，指向3，答案为left。
 * 
 * 2. k不存在：
 *  可以肯定，不论k存在与否，最后一定有 left==right，
 *       left
 *        ↓
 *        5
 *        ↑
 *       right
 * （1）如果k大于所有数，比如k=6，此时left和right共同指向最后一个数，下一步left++，left=n，超出范围，right不变，right=n-1;
 * （2）如果k小于所有数，比如k=4，此时left和right共同指向第一个数，下一步right--，right=-1，left不变，left=0，但是此时nums[left]!=val.
 * 
 * 3. 特殊情况：k存在，且所有数都等于k：
 *  left
 *   ↓
 *   5 5 5 5 5 5
 *   ↑
 *  right
 * 下一步right--，为-1，left不变，你会发现right=-1是合法值，此时k是存在的，所以不能通过right=-1判断k不存在。
 */
// 分类：1，val在中间；2，val在左；3，val在右；4，val比所有数大；5，val比所有数小
// 数组长度：奇数、偶数（循环跳出条件：left和right可能相等）
int leftBound(int nums[], int n, int val){
    if(nums==nullptr || n <= 0)
        return -1;
    
    int left = 0, right = n-1, mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(nums[mid] == val)
            right = mid - 1; // 收缩右边界
        else if(nums[mid] < val)
            left = mid + 1;
        else if(nums[mid] > val)
            right = mid - 1;
    }
    // if(right < 0 || left >= n) return -1; // right < 0 的判断错误，例如 4,4,4,5,7,8,9，那么right就等于-1
    // 特殊处理：如果没找到，返回-1
    if(left >= n || nums[left] != val)
        return -1;
    // left的值可以理解为，数组中小于val的数字个数
    return left; // left == right + 1
}

int rightBound(int nums[], int n, int val){
    if(nums==nullptr || n <= 0)
        return -1;
    
    int left = 0, right = n-1, mid;
    while(left <= right){
        mid = (left + right) / 2;
        if(nums[mid] == val)
            left = mid + 1; // 收缩左边界
        else if(nums[mid] < val)
            left = mid + 1;
        else if(nums[mid] > val)
            right = mid - 1;
    }
    if(right < 0 || nums[right] != val)
        return -1;
    return right;
}

/**
 * 思路：如果这个数不存在，在循环的倒数第二步，必然有 left==right，假设此时指向5：
 *       right
 *         ↓
 *      3  5 7
 *         ↑
 *        left
 * 如果要找的数比5大，比如k=6，下一步left++，指向7，right不变，还是指向5，答案为left;
 * 如果要找的数比5小，比如k=4，下一步right--，指向3，left不变，还是指向5，答案为left.
 * 
 * 如果要找的数不存在，若k比所有数都大，比如k=9，left不变，下一步left++，为n，超出范围，答案为-1
 *       right
 *         ↓
 *   1  3  5
 *         ↑
 *        left
 * 
 * 如果要找的数不存在，若k比所有的数都小，比如k=0，left不变，下一步right--，为-1，超出范围，答案为left
 *  right
 *   ↓
 *   1 2 3 5
 *   ↑
 *  left
 */
// 如果没有k，找到第一个比k大的位置，-1表示所有数都比k小
int binarySearch1(vector<int>& nums, int k) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (nums[mid] == k) {
			return mid; // 找到k
		}
		else if (nums[mid] > k) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return left >= nums.size() ? -1 : left; // 找到第一个比k大的位置，-1表示所有数都比k小
}

// 如果没有k，找到最后一个比k小的位置，-1表示所有数都比k大
int binarySearch2(vector<int>& nums, int k) {
	int left = 0, right = nums.size() - 1;
	while (left <= right) {
		int mid = (left + right) / 2;
		if (nums[mid] == k) {
			return mid; // 找到k
		}
		else if (nums[mid] > k) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}
	return right < 0 ? -1 : right; // 找到最后一个比k小的位置，-1表示所有数都比k大
}