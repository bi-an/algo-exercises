
// 题目：将word1转换成word2需要的操作数（最小编辑距离）

// 分析：动态规划, dp[i][j]表示子串word1[1~i]转换成子串word2[1~j]的最小编辑距离（最少操作数）。i=0或者j=0表示字串长度为0，即空。
// word1的第i个字符与word2的第j个字符比较：
// 1. 相等，不操作，dp[i][j]=dp[i-1][j-1];
// 2. 不相等：
//   2.1. 删除，dp[i][j]=dp[i-1][j]+1;
//   2.2. 替换，dp[i][j]=dp[i-1][j-1]+1;
//   2.3. 插入，dp[i][j]=dp[i][j-1]+1.

// 空间复杂度: O(n^2)
class Solution {
public:
	int minDistance(string word1, string word2) {
		int m = word1.size(), n = word2.size();
		// dp[i][j]表示子串word1[1~i]转换成子串word2[1~j]的最小编辑距离（最少操作数）。i=0或者j=0表示字串长度为0，即空。
		vector<vector<int>> dp(m+1,vector<int>(n+1,0));

		for (int i = 1; i <= m; i++) {
			dp[i][0] = i; // 子串word2为空，子串word1不为空，则编辑距离是子串word1的长度
		}
		for (int j = 1; j <= n; j++) {
			dp[0][j] = j;
		}

		for (int i = 1; i <= m;i++) {
			for (int j = 1; j <= n; j++) {
				if (word1[i - 1] == word2[j - 1]) { // 注意：word的下标从0开始，dp的下标从1开始
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
				}
			}
		}

		return dp[m][n];
	}
};


// 空间优化：注意到dp[i][j]只与dp[i-1][j-1]、dp[i-1][j]和dp[i][j-1]有关
// ---------------------------------
// |  |  |(i-1,j-1)|(i-1,j)|
// ----------------------------------
// |  |  | (i,j-1) | (i,j) |
// ----------------------------------
// |  |  |		   |       |
// ----------------------------------

// 改进1: 也就是说，只与之前的一行和当前的一行有关
// 空间复杂度: O(2*n)
class Solution{
public:
	int minDistance(string word1, string word2) {
		int m=word1.size(), n=word2.size();
		vector<int> cur(n+1), pre(n+1); // dp[0][j]都为j

		for(int j=0;j<=n;j++)
			pre[j]=j;

		for(int i=1;i<=m;i++){
			cur[0]=i; // dp[i][0]都为i
			for(int j=1;j<=n;j++){
				if(word1[i-1]==word2[j-1]){ // 注意：下标一定要注意，debug了好久
					cur[j]=pre[j-1];
				}
				else{
					cur[j]=min(pre[j-1],min(pre[j], cur[j-1]))+1;
				}
			}
            fill(pre.begin(), pre.end(), 0);
			swap(cur,pre);
		}
		return pre[n]; // 因为最后一次pre和cur交换了
	}
};

// 改进2：注意到实际上cur只需要之前的一个数
// 空间复杂度: O(n+1)
class Solution {
public:
	int minDistance(string word1, string word2) {
		int m = word1.size(), n = word2.size(), cur=m>n?m:n; // cur初始化为m和n的最大值，因为当m或者n为0时，将无法进入循环
		vector<int> pre(n + 1);

		for (int j = 0; j <= n; j++)
			pre[j] = j;

		for (int i = 1; i <= m; i++) {
			int temp = i; // dp[i][0]=i
			for (int j = 1; j <= n; j++) {
				if (word1[i - 1] == word2[j - 1])
					cur = pre[j - 1];
				else {
					cur = min(temp, min(pre[j - 1], pre[j])) + 1; // 加1一定不能忘记啊！！！一定要先把公式写准确再编程
				}
				pre[j - 1] = temp; // pre[j-1]下一次比较不再使用; 更新pre
				temp = cur;
			}
			pre[n] = temp; // pre最后一个元素更新
		}
		return cur;
	}
};

// 改进3：此处的cur保存上一行的结果
// 不同之处在于立即更新cur
class Solution {
public:
	int minDistance(string word1, string word2) {
		int m = word1.size(), n = word2.size(), pre;
		vector<int> cur(n + 1);

		for (int j = 0; j <= n; j++)
			cur[j] = j; // 如果n=0, cur也已经初始化了；只要m不为0，就会进入第一层循环

		for (int i = 1; i <= m; i++) {
			pre = cur[0]; // 此时的cur是上一次的
			cur[0] = i; // 立即更新cur
			for (int j = 1; j <= n; j++) {
				int temp = cur[j]; // cur[j]表示上一行的第j个记录
				if (word1[i - 1] == word2[j - 1])
					cur[j] = pre;
				else {
					cur[j] = min(pre, min(cur[j - 1], cur[j])) + 1; // 右边的cur[j]表示上一行的第j个记录
				}
				pre = temp;
			}
		}

		return cur[n];
	}
};