/*
 * @lc app=leetcode.cn id=744 lang=cpp
 *
 * [744] 寻找比目标字母大的最小字母
 */

// @lc code=start
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        auto i = /* ranges:: */ upper_bound(letters, target);
        if (i == letters.size())
            return letters[0];
        return letters[i];
    }

    int upper_bound(vector<char>& letters, char target) {
        int n = letters.size(), left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (letters[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
        return left;
    }
};
// @lc code=end
