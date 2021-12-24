// @Athor zzg
// 时间复杂度：O(mn)
class Solution {
    public int repeatedStringMatch(String a, String b) {
        int m = a.length(), n = b.length();

        for (int start = 0; start < m; start++) {
            if (a.charAt(start) != b.charAt(0))
                continue;
            int may = start == 0 ? 0 : 1;
            // i: 环状指针
            for (int i = start, j = 0; j < n; i++, i %= m, j++) {
                if (a.charAt(i) != b.charAt(j)) {
                    may = Integer.MAX_VALUE;
                    break;
                }
                if (i == 0)
                    may++;
            }
            if(may != Integer.MAX_VALUE)
                return may;
        }

        return -1;
    }
}

// TODO KMP、字符串哈希（Rabin Karp）
