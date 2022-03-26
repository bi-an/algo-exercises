/*
 * @Author: your name
 * @Date: 2022-03-26 17:21:07
 * @LastEditTime: 2022-03-26 17:21:07
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\167.两数之和II-输入有序数组.cc
 */


// 双指针
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ans(2);
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                ans[0] = left + 1;
                ans[1] = right + 1;
                break;
            } else if (sum < target) {
                ++left;
            } else {
                --right;
            }
        }
        return ans;
    }
};