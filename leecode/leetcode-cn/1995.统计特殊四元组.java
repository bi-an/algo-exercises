class Solution {
    public int countQuadruplets(int[] nums) {
        int n = nums.length;
        Map<Integer, Integer> cnt = new HashMap<>();
        int ans = 0;
        for (int b = n - 3; b >= 1; b--) {
            for (int d = b + 2; d < n; d++) {
                int sub = nums[d] - nums[b + 1];
                cnt.put(sub, cnt.getOrDefault(sub, 0) + 1);
            }
            for (int a = 0; a < b; a++) {
                ans += cnt.getOrDefault(nums[a] + nums[b], 0);
            }
        }

        return ans;
    }
}
