namespace solution_1
{

// 直接排序
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> res(nums);
        // std::sort(res.begin(), res.end(), [](const int& a, const int& b) {
        //     return abs(a) < abs(b);
        // });
        for (int i = 0; i < res.size(); ++i) {
            res[i] = res[i] * res[i];
        }
        std::sort(res.begin(), res.end());
        return res;
    }
};

} // namespace solution_1


namespace solution_2
{
// 双指针方法一
// 找出最后一个负数的下标
// 然后从中间向两边遍历
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        int negetive = -1;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < 0)
                negetive = i;
            else
                break;
        }

        vector<int> res(n);
        int i = negetive, j = negetive + 1, k = 0;
        while (i >= 0 || j < n) {
            if (i < 0) {
                res[k++] = nums[j] * nums[j];
                ++j;
            } else if (j >= n) {
                res[k++] = nums[i] * nums[i];
                --i;
            } else if (nums[i] * nums[i] < nums[j] * nums[j]) {
                res[k++] = nums[i] * nums[i];
                --i;
            } else {
                res[k++] = nums[j] * nums[j];
                ++j;
            }
        }
        return res;
    }
};

} // namespace solution_2

namespace solution_3
{

// 双指针方法二
// 由于最大的数一定在两边(负得最多或正得最多,即绝对值最大)
// 我们可以使用双指针分别从两边向中间遍历
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        for (int i = 0, j = n - 1, pos = n - 1; pos >= 0; pos--) {
            if (nums[i] * nums[i] > nums[j] * nums[j]) {
                res[pos] = nums[i] * nums[i];
                i++;
            } else {
                res[pos] = nums[j] * nums[j];
                j--;
            }
        }
        return res;
    }
};

} // namespace solution_3
