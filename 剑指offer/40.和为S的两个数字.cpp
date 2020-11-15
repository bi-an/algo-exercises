/*
输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。
*/
class Solution
{
 public:
  vector<int> FindNumbersWithSum(vector<int> array, int sum)
  {
    vector<int> res;
    if (array.size() < 2)
      return res;
    //当a和b尽可能地接近时，a*b最大。也就是说，当a和b尽可能地远离时，a*b最小。
    int left = 0, right = array.size() - 1;

    while (right > left)
    {
      int curSum = array[left] + array[right];
      if (curSum == sum)
      {
        res.push_back(array[left]);
        res.push_back(array[right]);
        break;
      }
      if (curSum < sum)
      {
        left++;
      }
      if (curSum > sum)
      {
        right--;
      }
    }

    return res;
  }
};