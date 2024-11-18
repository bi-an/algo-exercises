/*
 * @Author: your name
 * @Date: 2022-03-26 21:14:29
 * @LastEditTime: 2022-03-26 23:20:12
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\1.两数之和.cc
 */

// 哈希表
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num2pos; // num2pos
        // 关键：一边遍历一边寻找另一个数，这样可保证不会匹配自身
        for (int i = 0; i < nums.size(); ++i) {
            int x = target - nums[i];
            if (num2pos.find(x) != num2pos.end())
                return vector<int>{num2pos[x], i};
            num2pos[nums[i]] = i;
        }
        return vector<int>{-1, -1};
    }
};