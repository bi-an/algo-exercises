class Solution {
    public int countKDifference(int[] nums, int k) {
        Map<Integer, Integer> cnt = new HashMap<>();
        int ans = 0;
        for (int x : nums) {
            ans += cnt.getOrDefault(x + k, 0);
            ans += cnt.getOrDefault(x - k, 0);
            cnt.put(x, cnt.getOrDefault(x, 0) + 1);
        }
        return ans;
    }
}