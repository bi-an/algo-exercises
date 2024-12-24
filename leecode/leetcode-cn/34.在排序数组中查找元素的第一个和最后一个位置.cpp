/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int l = lower_bound(nums, target);
        // 判断返回的指针所指元素是否等于 taregt
        if (l == nums.size() || nums[l] != target)
            return {-1, -1};

        /** 以下写法效率不一定高，因为可能整个数组全部等于 target */
        /**
        int r = l - 1;
        while (r + 1 < n && nums[r + 1] == target)
            ++r;
        return {l, r};
        */

        int r = lower_bound3(nums, target + 1);
        return {l, r - 1};
    }

    // lower_bound 第一个等于 target 的下标
    //
    // 红蓝染色法
    // 红色区域： < target
    // 蓝色区域： ≥ target
    // 白色区域： 未确定
    // 显然我们需要在当前颜色区域的补集中搜寻，注意：即使等于也要向左继续搜寻。
    //
    // 闭区间写法：[left, right]
    // (1) 如果 mid 处于红色区域，则 left = mid + 1；
    // (2) 如果 mid 处于蓝色区域，则 right = mid - 1 。
    // 总结：更新区间后，left 总是指向红色区域的下一个；right 总是指向蓝色区域的上一个。
    // 故循环结束时，left 指向的是蓝色区域的第一个；right 指向的是蓝色区域的上一个。
    int lower_bound(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;  // 闭区间初始化
        // 循环条件：闭区间
        while (left <= right) {
            // mid 偏左
            // int mid = (left + right) / 2; // 可能溢出
            int mid = left + (right - left) / 2;  // 不会溢出
            if (nums[mid] >= target)
                right = mid - 1;  // 即使等于也要向左搜寻
            else
                left = mid + 1;  // 小于部分全部不满足
        }
        // 指向蓝色区域第一个元素
        // 如果没有找到 target ，那么返回的指针：要么元素大于 target ，要么指向 n （当 nums 所有元素都小于 target）。
        return left;  // 或 right - 1
    }

    // 左闭右开区间写法：[left, right)
    // 更新区间后，left 始终指向红色区域下一个元素；right 始终指向蓝色区域第一个。
    // 循环结束时，left 指向蓝色区域第一个，right 也指向蓝色区域第一个。
    int lower_bound2(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid;  // 右开区间
            else
                left = mid + 1;  // 左闭区间
        }
        return left;  // 或 right
    }

    // 开区间写法：(left, right)
    // 更新区间后，left 始终指向红色区域最后一个，right 始终指向蓝色区域第一个。
    // 循环结束时，left 指向红色区域最后一个，right 指向蓝色区域第一个。
    int lower_bound3(vector<int>& nums, int target) {
        int left = -1, right = nums.size();
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
                right = mid;  // 右开区间
            else
                left = mid;  // 左开区间
        }
        return right;  // 或 left + 1
    }
};
// @lc code=end
