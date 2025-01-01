/*
 * @lc app=leetcode.cn id=658 lang=cpp
 *
 * [658] 找到 K 个最接近的元素
 */

// 二分 + 双指针
// 时间复杂度：O(logn + k)
// 空间复杂度：O(1)
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int i = ranges::lower_bound(arr, x) - arr.begin();
        // 因为 i 偏右，所以取 i-1 和 i
        int l = i - 1, r = i, n = arr.size();
        while (k > 0) {
            if (r == n || l >= 0 && x - arr[l] <= arr[r] - x)
                l--;
            else /*if (l < 0 || r < n && x - arr[l] > arr[r] - x)*/
                r++;
            k--;
        }
        // return vector<int>(arr.begin() + l + 1, arr.begin() + l + 1 + k);
        return vector<int>(arr.begin() + l + 1, arr.begin() + r);
    }
};

namespace solution_2 {

// @lc code=start
// 官方题解一：https://leetcode.cn/problems/find-k-closest-elements/solutions/1771732/zhao-dao-k-ge-zui-jie-jin-de-yuan-su-by-ekwtd/
// 按照「更接近」的定义重新排序
// 时间复杂度：O(nlogn)
// 空间复杂度：O(logn) ，排序需要 O(logn) 的栈空间
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        ranges::sort(arr, [=](int a, int b) { return abs(a - x) < abs(b - x) || abs(a - x) == abs(b - x) && a < b; });
        sort(arr.begin(), arr.begin() + k);
        return vector<int>(arr.begin(), arr.begin() + k);
    }
};
// @lc code=end

}  // namespace solution_2
