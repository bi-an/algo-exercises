// @brief KMP算法
// 时间复杂度：O(m+n)
// 空间复杂度：O(n)
class Solution {
    public int strStr(String haystack, String needle) {
        int m = haystack.length(), n = needle.length();
        if(n == 0)
            return 0; // 注意

        int[] next = new int[n];

        // needle[0,...,j-1]与needle[i-j,...,i-1]是匹配的，也就是已经匹配的子串。
        // j是下一个需要比较的位置。
        // next[k]记录下已经匹配到第k个字符（包括）时，下一个需要比较的位置。也就是说，
        // [0,...next[k-1]]一定是匹配的。
        //
        // next数组表示前后公共缀长度
        // https://segmentfault.com/q/1010000014560162
        //
        // next[i] 表示子串对齐的下一个位置，或者说已经对齐匹配的长度。
        // next[i]的连续序列（从1开始）对应的子串，与模式串前缀是匹配的。
        // 例如 pattern = "caabacabacaabaf"
        // pattern: c   a   a   b   c   a   a   b   a   c   a   d   b   c   f
        // next:    0   0   0   0   1   2   3   4   0   1   2   0   0   1   0

        // next[0] = 0; // Java会默认初始化
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && needle.charAt(i) != needle.charAt(j))
                j = next[j - 1]; // 注意，倒退到next[j-1]时，还没有进行比较，所以比较后还可能再次倒退。
            if (needle.charAt(i) == needle.charAt(j))
                j++; // 当前匹配，j指向下一个需要比较的位置
            next[i] = j;
        }

        // 开始比较
        // i 没有回退
        // j
        for (int i = 0, j = 0; i < m && j < n; i++) {
            while (j > 0 && haystack.charAt(i) != needle.charAt(j))
                j = next[j - 1];
            if (haystack.charAt(i) == needle.charAt(j))
                j++;
            if (j == n)
                return i - n + 1;
        }

        return -1;
    }
}
