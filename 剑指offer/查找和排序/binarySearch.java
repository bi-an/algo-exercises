class Solution {
    // @ret 取值范围 [0, nums.length]
    // 如果lower为true，那么返回的iterator指向第一个等于或大于（不存在时）target的位置，
    //  与C++ lower_bound()相同；
    // 如果lower为false，那么返回的iterator指向第一个大于target的位置，
    //  与C++ upper_bound()相同。
    public static int binarySearch(int[] nums, int target, boolean lower) {
        int left = 0, right = nums.length - 1;
        int ans = nums.length; // 注意
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    // Test
    public static void main(String[] args) {
        Solution solution = new Solution();
        int[] nums = new int[]{3, 4, 5, 5, 6, 9, 10};

        System.out.println(binarySearch(nums, 2, true)); // 0
        System.out.println(binarySearch(nums, 5, true)); // 2
        System.out.println(binarySearch(nums, 50, true)); // 7

        System.out.println(binarySearch(nums, 2, false)); // 0
        System.out.println(binarySearch(nums, 5, false)); // 4
        System.out.println(binarySearch(nums, 50, false)); // 7
    }
}