/*
 * @Author: bi_an:desktop 2608120872@qq.com
 * @Date: 2022-06-18 18:08:26
 * @LastEditors: bi_an:desktop 2608120872@qq.com
 * @LastEditTime: 2022-06-18 18:13:53
 * @FilePath: \practice\leecode\leetcode-cn\491.递增子序列.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

// 时间复杂度：O(n*2^n)
//      每个数字选或不选，所以 n 个数字共有 2^n 中选择。但是，还需 O(n) 的时间复制到答案中。TODO: 没懂
// 空间复杂度：O(n)
//      不包括返回值的空间，临时数组空间为 O(n)
class Solution {
    vector<vector<int>> ans;
    vector<int> temp; // temporary sequence

    void dfs(int cur, int last, vector<int>& nums) {
        if (cur >= nums.size()) {
            if (temp.size() >= 2) {
                ans.push_back(temp);
            }
            return;
        }
        /// 选择 cur
        if (nums[cur] >= last) {
            temp.push_back(nums[cur]);
            dfs(cur + 1, nums[cur], nums);
            temp.pop_back();
        }
        /// 不选择 cur
        // if 用来去重（剪枝）
        // 例如 {1,3,2} => {1,2} （不选3）
        // 例如 {1,2,3} => {1,3} （不选2）
        // 例如 {1,2,2} => 跳过，因为上一次已经计入了 {1,2}
        if (nums[cur] != last) {
            dfs(cur + 1, last, nums);
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        dfs(0, INT_MIN, nums);
        return ans;
    }
};