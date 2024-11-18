/**
 * 给定一个未排序的整数数组，找出最长连续序列的长度。
 * 
 * 要求算法的时间复杂度为 O(n)。
 * 
 * 示例:
 * 
 * 输入: [100, 4, 200, 1, 3, 2]
 * 输出: 4
 * 解释: 最长连续序列是 [1, 2, 3, 4]。它的长度为 4。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/longest-consecutive-sequence
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


#include <vector>
#include <set>
using namespace std;

// O(nlogn)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.size() == 0) return 0;

        set<int> myset;
        for (int i = 0; i < nums.size(); i++) {
            myset.insert(nums[i]);
        }
        int ans = 1, curLen = 1;
        for (auto it = myset.begin(); it != myset.end();) {
            int val = *it;
            if (++it != myset.end() && *it - 1 == val) {
                curLen++;
            }
            else {
                if (ans < curLen)
                    ans = curLen;
                curLen = 1;
            }
        }
        return ans;
    }
};