// TODO: 为什么java比cpp快3倍左右？

// 写法一
class Solution {
  public int threeSumClosest(int[] nums, int target) {
      int n = nums.length;

      Arrays.sort(nums);

      int ans = nums[0] + nums[1] + nums[2]; // 也可以根据数值范围初始化

      for (int i = 0; i < n - 2; i++) {
          int p1 = i + 1, p2 = n - 1;
          while (p1 < p2) {
              int sum = nums[i] + nums[p1] + nums[p2];
              if (Math.abs(sum - target) < Math.abs(ans - target))
                  ans = sum;
              if (sum == target) {
                  // 优化：提前退出
                  return sum;
              } else if (sum < target) {
                  int p = p1 + 1;
                  // 优化：移动到下一个不同的数
                  while (p < p2 && nums[p] == nums[p1])
                      p++;
                  p1 = p;
              } else {
                  int p = p2 - 1;
                  while (p > p1 && nums[p] == nums[p2])
                      p--;
                  p2 = p;
              }
          }
      }

      return ans;
  }
}

// 写法二：leetcode用户的优化。
// 测试结果为：写法一运行 120 ms，该优化解法运行 7 ms.
class Solution {
  public int threeSumClosest(int[] nums, int target) {
      Arrays.sort(nums);
      int result = nums[0] + nums[1] + nums[2];
      for(int i=0;i<nums.length-2;i++){
          int left = i+1;
          int right = nums.length - 1;
          while(left != right){
              int min = nums[i] + nums[left] + nums[left + 1];
              if(target < min){
                  if(Math.abs(result - target) > Math.abs(min - target))
                      result = min;
                  break;
              }
              int max = nums[i] + nums[right] + nums[right - 1];
              if(target > max){
                  if(Math.abs(result - target) > Math.abs(max - target))
                      result = max;
                  break;  
              }
              int sum = nums[i] + nums[left] + nums[right];
              // 判断三数之和是否等于target
              if(sum == target)
                  return sum;
              if(Math.abs(sum - target) < Math.abs(result - target))
                  result = sum;
              if(sum > target){
                  right--;
                  while(left != right && nums[right] == nums[right+1])
                      right--;
              }
              else{
                  left++;
                  while(left != right && nums[left] == nums[left-1])
                      left++;
              }
          }
          while(i<nums.length-2 && nums[i] == nums[i+1])
              i++;
      }
      return result;
  }
}

// 作者：已注销
// 链接：https://leetcode.cn/problems/3sum-closest/solution/dui-shuang-zhi-zhen-fa-jin-xing-yi-dian-you-hua-da/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。