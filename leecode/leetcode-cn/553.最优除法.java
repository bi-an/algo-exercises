/*
 * @Author: your name
 * @Date: 2022-02-28 22:37:19
 * @LastEditTime: 2022-02-28 22:51:00
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\553.最优除法.java
 */


// 方法一：数学分析
// 最大值 = 最大分子 / 最小分母
//   1. 分子：由数值范围，数组中每个元素都大于1，所以其除以后面的数都会变小，所以
//          最大分子 = nums[0]；
//   2. 分母：考虑表达式 a/b/c/d/e/f，其中，每个数都大于1，那么，我们在任意位置加上括号，都使得括号中的除号变成乘号，例如
//      例如：a/(b/c/d)/e/f = a/(b/c)*d/e/f = a/b*c*d/e/f, 由于每个数都大于1，所以添加任意的括号都会使得原来的表达式变大。
//      所以，分母中不应该出现任何括号，即
//          最小分母 = nums[1]/nums[2]/...
//   综上：最大值 = nums[0] / (nums[1]/nums[2]/...)
// @ref 官方题解
// 时间复杂度
class Solution {
    public String optimalDivision(int[] nums) {
        int n = nums.length;
        if (n == 1)
            return String.valueOf(nums[0]);
        if (n == 2)
            return String.valueOf(nums[0]) + "/" + String.valueOf(nums[1]);
        StringBuffer sb = new StringBuffer();
        sb.append(String.valueOf(nums[0]) + "/(");
        for (int i = 1; i < n - 1; i++) {
            sb.append(String.valueOf(nums[i]) + "/");
        }
        sb.append(String.valueOf(nums[n - 1]) + ")");
        return sb.toString();
    }
}

// 方法二：动态规划
// @ref 官方题解
// 时间复杂度：O(n^3)
// 空间复杂度：O(n^2)
class Solution {
    public String optimalDivision(int[] nums) {
        int n = nums.length;
        Node[][] dp = new Node[n][n]; // Attention: Initilized with null

        // dp[i][j] 表示 nums[i...j] 所能表示的表达式的最大值和最小值
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = new Node();
            }
            dp[i][i].minVal = nums[i];
            dp[i][i].maxVal = nums[i];
            dp[i][i].minStr = String.valueOf(nums[i]);
            dp[i][i].maxStr = String.valueOf(nums[i]);
        }

        // 沿对角线填 dp 表格
        // j 是长度, i 是起始下标
        for (int j = 1; j < n; j++) {
            for (int i = 0; i + j < n; i++) {
                for (int k = 0; k < i + j; k++) {
                    if (dp[i][i + j].minVal > dp[i][k].minVal / dp[k + 1][i + j].maxVal) {
                        dp[i][i + j].minVal = dp[i][k].minVal / dp[k + 1][i + j].maxVal;
                        if (k + 1 == i + j)
                            dp[i][i + j].minStr = dp[i][k].minStr + "/" + dp[k + 1][i + j].maxStr;
                        else
                            dp[i][i + j].minStr = dp[i][k].minStr + "/(" + dp[k + 1][i + j].maxStr + ")";
                    }
                    if (dp[i][i + j].maxVal < dp[i][k].maxVal / dp[k + 1][i + j].minVal) {
                        dp[i][i + j].maxVal = dp[i][i].maxVal / dp[k + 1][i + j].minVal;
                        if (k + 1 == i + j)
                            dp[i][i + j].maxStr = dp[i][k].maxStr + "/" + dp[k + 1][i + j].minStr;
                        else
                            dp[i][i + j].maxStr = dp[i][k].maxStr + "/(" + dp[k + 1][i + j].minStr + ")";
                    }
                }
            }
        }

        return dp[0][n - 1].maxStr;
    }
}