// 写法一
void reverse(vector<int> &nums)
{
  int n = nums.size();
  for (int i = 0; i < n / 2; i++)
    swap(nums[i], nums[n - 1 - i]);
}

// 写法二：参考STL
void reverse(vector<int> &nums)
{
  int n = nums.size();
  for (int i = 0, j = n - 1; i < j; i++, j--)
    swap(nums[i], nums[j]);
}