class Solution {
    public List<List<Integer>> fourSum(int[] nums, int target) {
        List<List<Integer>> ans = new ArrayList<>();
        int n = nums.length;

        // 先排序
        Arrays.sort(nums);

        for (int i = 0; i < n - 3; i++) {
            // 去重
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            long curSum = nums[i]; // 四个数之和可能会溢出
            // 剪枝
            if (curSum + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
                break;

            if (curSum + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
                continue;

            for (int j = i + 1; j < n - 2; j++) {
                // 去重
                if (j > i + 1 && nums[j] == nums[j - 1])
                    continue;
                // 剪枝
                curSum = nums[i] + nums[j];
                if (curSum + nums[j + 1] + nums[j + 2] > target)
                    break;
                if (curSum + nums[n - 2] + nums[n - 1] < target)
                    continue;
                int left = j + 1, right = n - 1;
                while (left < right) {
                    curSum = nums[i] + nums[j] + nums[left] + nums[right];
                    if (curSum == target) {
                        ans.add(Arrays.asList(nums[i], nums[j], nums[left], nums[right]));
                        // 去重，所以left和right可以同时移动
                        while (left < right && nums[left] == nums[left + 1])
                            left++;
                        left++;
                        while (left < right && nums[right] == nums[right - 1])
                            right--;
                        right--;
                    } else if (curSum > target) {
                        // 去重
                        while (left < right && nums[right] == nums[right - 1])
                            right--;
                        right--;
                    } else {
                        // 去重
                        while (left + 1 < right && nums[left] == nums[left + 1])
                            left++;
                        left++;
                    }
                }
            }
        }

        return ans;
    }
}