// 1. 要想容积尽可能大，只能left和right的距离尽可能拉开
// 所以起始时left和right分别位于最左端和最右端
// 2. 容积取决于left和right中的较小高度
// 3. 只有中间的高度高于left和right中的较小高度时，才可能有更高的容积
// 综合2和3，更新左右端时，应该移动其中的较小高度的那一端
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = (int)(height.size()) - 1, ans = 0;
        while(left < right) {
            int h = min(height[left], height[right]);
            ans = max(h * (right - left), ans);
            height[left] < height[right] ? left++ : right--;
        }
        return ans;
    }
};