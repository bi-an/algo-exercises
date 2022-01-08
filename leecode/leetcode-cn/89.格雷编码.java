// 对称翻转
// 发现规律：将之前的数倒序遍历一遍，然后在每个数的高位增加一个二进制1可以得到下一个格雷码。
class Solution {
    public List<Integer> grayCode(int n) {
        List<Integer> ans = new ArrayList<>(1 << n);
        ans.add(0);
        for (int i = 1; i <= n; i++) {
            int L = ans.size();
            for (int j = L - 1; j >= 0; j--) {
                ans.add(ans.get(j) | L); // L = (1 << (i - 1))
            }
        }
        return ans;
    }
}