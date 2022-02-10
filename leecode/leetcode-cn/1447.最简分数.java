class Solution {
    public List<String> simplifiedFractions(int n) {
        List<String> ans = new ArrayList<>();
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (gcd(i, j) == 1) {
                    ans.add(j + "/" + i);
                }
            }
        }
        return ans;
    }

    // 辗转相除法 最大公约数
    // @ref https://lucifer.ren/leetcode/thinkings/GCD.html
    public int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}