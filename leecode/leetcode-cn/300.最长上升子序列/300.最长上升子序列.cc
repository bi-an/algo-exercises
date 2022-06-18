#include <bits/stdc++.h>
using namespace std;

/**
 * @ref labuladong
 * 
 */

// 动态规划
// 时间复杂度O(n^2)，空间复杂度O(n)
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;

		int n = nums.size();
		// dp[i]表示以第i个字符结尾（一定包含该字符）的子序列中，最长的长度
        // 注意：dp[i]不是最优值
		vector<int> dp(n);
		for (int i = 0; i < n; i++)
			dp[i] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = i - 1; j >= 0; j--) {
                // 此时可以把nums[i]直接接到nums[j]后面，所以最长长度要加1
				if (nums[i] > nums[j]) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
		}

		return *max_element(dp.begin(), dp.end());
	}
};


// 模拟纸牌Patience Solitaire
// 纸牌的堆数就是最长子序列长度，证明见《LongestIncreasingSubsequence.pdf》
// 时间复杂度O(nlogn)，空间复杂度O(n)
class Solution_2 {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;

		int piles = 0;
        // top是有序的，所以可以使用二分法
        vector<int> top(nums.size());
        for(int i=0;i<nums.size();i++){
            int left = 0, right = piles - 1;
			// 左边界的二分查找法
            while(left <= right){
                int mid = (left+right)/2;
                if(top[mid] >= nums[i]){
                    right = mid - 1; // 即使等于，也要不断往左寻找
                }
                else {
                    left = mid+1;
                }
            }
            // 没有合适的堆，则新建一个
            if(left == piles){
                top[piles++] = nums[i];
            }
            else{
                top[left] = nums[i];
            }
        }

        return piles;
	}
};

// 贪心 + 二分查找
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), len = 1; // len表示dp长度
        // 贪心：要想子序列尽可能长，那么在所有长度i的递增子序列中，应该选择结尾值最小的那个
        vector<int> d(n, INT_MAX); // d[i]为长度为i的最长递增子序列的最小元素。(0)
        // 反证法可以证明，dp[i]是关于i的递增函数。
        // 证明：假设 d[i] 不是关于 i 的递增函数，则存在 j < i, d[j] > d[i]。(1)
        // 我们从 d 中删除 d[j+1,...,i]，得到新序列长度为 j，设此时 j 位置的元素为 x，
        // 那么，x >= d[j]。(2)
        // 结合 (1) 和 (2)，得到 x > d[i]。于是，我们在原来的序列中找到了一个 x ，它大于 d[i]。
        // 这与我们的定义 (0) 矛盾。得证。
        d[0] = nums[0];
        for(int i = 1; i < n; i++) {
            if(nums[i] > d[len - 1]) {
                d[len++] = nums[i];
            } else {
                // 找到第1个大于或等于nums[i]的位置，更新d
                int left = 0, right = len - 1;
                while(left <= right) {
                    int middle = (left + right) / 2;
                    if(d[middle] > nums[i])
                        right = middle - 1;
                    else if(d[middle] < nums[i])
                        left = middle + 1;
                    else {
                        left = middle;
                        break;
                    }
                }
                d[left >= len ? right : left] = nums[i];
            }
        }
        return len;
    }
};

// 二分查找写法二
// https://leetcode-cn.com/problems/longest-increasing-subsequence/solution/zui-chang-shang-sheng-zi-xu-lie-by-leetcode-soluti/
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) {
            return 0;
        }
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) {
                d[++len] = nums[i];
            } else {
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};
