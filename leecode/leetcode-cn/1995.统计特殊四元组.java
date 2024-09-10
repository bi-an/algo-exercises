class Solution {
    public int countQuadruplets(int[] nums) {
        int n = nums.length;
        Map<Integer, Integer> cnt = new HashMap<>();
        int ans = 0;
        // 假设固定a,b
        for (int b = n - 3; b >= 1; b--) {
            // 由于d是逆序的，最开始c,d都只有一个取值。
            // (1) 假设c∈[k,...]，此时d∈[k+1,n-1]；
            // (2) 当c向左移动一格，c∈[k-1,...]，此时d∈[k,n-1]，
            // 中间情况∀c∈[k,...]，且d∈[k+1,n-1]，都在第(1)步中计算过了。
            // 所以此时只需要计算c=k的情况。
            for (int d = b + 2; d < n; d++) {
                int sub = nums[d] - nums[b + 1]; // c = b+1
                cnt.put(sub, cnt.getOrDefault(sub, 0) + 1);
            }
            for (int a = 0; a < b; a++) {
                ans += cnt.getOrDefault(nums[a] + nums[b], 0);
            }
        }

        return ans;
    }
}
