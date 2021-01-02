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
    // if(right < 0 || left >= n) return -1; // right < 0 的判断错误
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