class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int r = 0, w = 0; // 读、写指针
        int n = nums.size();
        while (r < n) {
            if (nums[r] != val)
                nums[w++] = nums[r];
            ++r;
        }
        return w;
    }
};