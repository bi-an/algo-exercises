// 参考官方题解
// 方法一：模拟
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
    public String pushDominoes(String dominoes) {
        char[] s = dominoes.toCharArray();
        int i = 0, n = dominoes.length();
        char left = 'L'; // 假设最左边有个 L，这样不会影响骨牌的最终状态
        while(i < n) {
            int j = i;
            // 找出竖立的一段骨牌
            while(j < n && s[j] == '.')
                j++;
            // 假设最右边有个 R
            char right = j < n ? s[j] : 'R';
            if(left == right) {
                // 如果这段竖立的骨牌的左右两边骨牌的方向相同，那么这段骨牌也倒向这一边
                while(i < j)
                    s[i++] = left;
            } else if(left == 'R' && right == 'L') {
                // 此时这段竖立骨牌向中间倾倒
                int k = j - 1;
                while(i < k) {
                    s[i++] = 'R';
                    s[k--] = 'L';
                }
            } // 其他情况下，这段竖立的骨牌保持原来的竖立状态
            left = right;
            i = j + 1;
        }
        return new String(s);
    }
}