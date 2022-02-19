// 分治法
// 思路：如果子串中某个字符出现（重复）的次数小于 K, 那么一定不是“至少有 K 个重复字符的子串”。
// 故而我们可以将字符串以该字符为界分割，然后再在分割好的两个子串中重复以上逻辑。
// 时间复杂度：O(n*C)。其中 n = s.length, C = 26 为递归深度，
//      因为每次递归都会完全排除某种字符，所以，最大递归深度为 C.
// 空间复杂度：O(C^2)。递归深度为 O(C)，每次递归需要 O(C) 空间。
class Solution {
    private int k;

    public int longestSubstring(String s, int k) {
        this.k = k;
        return dfs(s, 0, s.length() - 1);
    }

    public int dfs(String s, int l, int r) {
        int[] cnt = new int[26];
        for (int i = l; i <= r; i++)
            cnt[s.charAt(i) - 'a']++;
        // 寻找第一个 split
        char split = 0;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] > 0 && cnt[i] < k) {
                split = (char) (i + 'a');
                break;
            }
        }
        // 所有字符重复次数都大于等于 K
        if (split == 0)
            return r - l + 1;
        int i = l;
        int ret = 0;
        while (i <= r) {
            // 找到第一个不为 split 的字符位置
            while (i <= r && s.charAt(i) == split)
                i++;
            if (i > r)
                break;
            int index = i;
            // 找到第一个为 split 的字符位置
            while (i <= r && s.charAt(i) != split)
                i++;
            int length = dfs(s, index, i - 1);
            ret = Math.max(ret, length);
            // 循环：分割下一个子串
        }
        return ret;
    }
}