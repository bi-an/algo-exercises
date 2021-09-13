// https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/
// 官方题解
class Solution {
public:
    int findIntegers(int n) {
		vector<int> dp(31); // 1<=n<=1e9, 30bit作为有效节点，1bit作为根节点（不含数字）
		dp[0] = dp[1] = 1; // 从下标1开始，也就是从根的孩子开始
		
		for(int i=2;i<31;i++)
			dp[i] = dp[i-1] + dp[i-2]; // 高度为i、根为0的字典满二叉树中符合要求的路径个数
		
        // 追溯字典最后一条路径
		int pre = 0, res = 0;
		for(int i=29;i>=0;i--) {
			int val = (1 << i);
			if((val & n) != 0) {
				// 左兄弟为满二叉树，记下
				res += dp[i+1]; // 从下标1开始
				if(pre == 1)
					break; // 有连续的'1'，停止计入；注意到此前通过不断记录其左兄弟，已经将所有路径都包含了
				pre = 1;
			} else {
				pre = 0;
			}
			
			if(i == 0)
				++res; // 此前已经将其左兄弟全部包含了，此时计入当前节点本身；由于连续的'1'已经被剔除了，此时不论'0'或'1'都符合要求
		}
		
		return res;
    }
};