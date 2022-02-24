class Solution {
    public int[] findBall(int[][] grid) {
        int n = grid[0].length;
        int[] ans = new int[n];
        for(int i = 0;i<n;i++) {
            int col = i; // 初始列
            for(int[] row : grid) {
                int dir = row[col];
                col += dir;
                // 只有到达边界或者遇到"V"字形，才会卡住
                // 否则，球遇到左挡板进入下一行左边，遇到右挡板进入下一行右边
                if(col == -1 || col == n || dir != row[col]) {
                    col = -1;
                    break;
                }
            }
            ans[i] = col;
        }
        return ans;
    }
}
/*
 * @Author: your name
 * @Date: 2022-02-24 23:18:44
 * @LastEditTime: 2022-02-24 23:18:49
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\1706.球会落何处.java
 */
