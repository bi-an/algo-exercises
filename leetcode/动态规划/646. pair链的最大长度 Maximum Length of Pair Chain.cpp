/*
You are given n pairs of numbers. In every pair, the first number is always smaller than the second number.

Now, we define a pair (c, d) can follow another pair (a, b) if and only if b < c. Chain of pairs can be formed in this fashion.

Given a set of pairs, find the length longest chain which can be formed. You needn't use up all the given pairs. You can select pairs in any order.

Example 1:
Input: [[1,2], [2,3], [3,4]]
Output: 2
Explanation: The longest chain is [1,2] -> [3,4]

Note:
The number of given pairs will be in the range [1, 1000].
*/

// 本题的所有pair都是符合要求的，不需要考虑。只是要求链的最大长度。
// 贪心算法
class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		// 重点：必须用pair的第二个数排序，因为每次比较都是用前一个pair的第二数与当前pair的第一个数比较，
		// 这样选第二个数小的总是能比选第二个数大的得到的链上节点数多。如：(1,2),(0,3),(3,4)
		// 如果用pair的第一个数排序，那么应该倒过来遍历。如: (1,4),(2,3),(4,5)
		std::sort(pairs.begin(), pairs.end(), [](vector<int>& a, vector<int>& b) {return a[1] < b[1]; });
		int end = std::numeric_limits<int>::min(), res = 0;
		for (auto& pair : pairs) {
			if (pair[0] > end) {
				res++;
				end = pair[1];
			}
		}
		return res;
	}
};

// 贪心算法，倒过来遍历，与上面是一样的
// 时间复杂度(nlogn)
class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		std::sort(pairs.begin(),pairs.end(),[](vector<int>& a, vector<int>& b){return a[0]<b[0];}); // 时间复杂度O(nlogn), 空间复杂度可能为O(1)或O(n)
		int res=0, begin=std::numeric_limits<int>::max();
		for(int i=pairs.size()-1;i>=0;i--){ // 时间复杂度O(n)
			auto &pair=pairs[i];
			if(pair[1]<begin){
				res++;
				begin=pair[0];
			}
		}
		return res;
	}
};

// 动态规划
// 时间复杂度: O(n^2)
// 空间复杂度: O(n)
class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
        std::sort(pairs.begin(),pairs.end(),[](auto &a, auto &b){return a[0]<b[0];});
		int n=pairs.size();
		vector<int> dp(n,1); // dp[i]表示pairs[0]~pairs[i]所能得到的最大链长
		for(int j=1;j<pairs.size();j++){
			for(int i=0;i<j;i++){
				if(pairs[i][1]<pairs[j][0])
					dp[j]=std::max(dp[j],dp[i]+1);
			}
		}
		// int ans=0;
		// for(auto x : dp)
		// 	if(x > ans)
		// 		ans=x;
		// return ans;
		return dp[n-1];
	}
};