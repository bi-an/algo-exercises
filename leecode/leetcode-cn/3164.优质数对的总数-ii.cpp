/*
 * @lc app=leetcode.cn id=3164 lang=cpp
 *
 * [3164] 优质数对的总数 II
 */

#include <bits/stdc++.h>
using namespace std;

// @lc code=start
// 这题的关键在于时间复杂度的取舍
// 假设我们总是用 nums1[i] 去匹配 nums2[j] ，这样时间复杂度为 O(nm) ，其中 n, m 都可能达到 10^5 。

// 方法一：如果我们找出 nums1[i]/k （需要能整除）的所有因子，时间复杂度为 O( sqrt(nums1[i]/k) ) ，也就是 10^3 ，这个过程与 nums2 无关；
// 但是同时我们可以将 nums2 及其频次存入哈希表，
// 对于每个 nums1[i] 的因子，可以在 O(1) 时间内找到 nums2[j] 的个数
// 这样将 nums1 和 nums2 解耦了。
// 时间复杂度变为 O(n sqrt(U/k) + m) ，其中 U 是最大的 nums1[i] 。
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<long long,int> cnt2;
        for (int x : nums2) {
            cnt2[static_cast<long long>(x) * k]++;
        }
        long long ans = 0;
        for (int num1 : nums1) {
            // 求 num1 的所有因子
            for (int x = 1; x * x <= num1; ++x) {
                if (num1 % x)
                    continue;
                if (cnt2.contains(x))
                    ans += cnt2[x];
                // 因子总是成对出现
                int y = num1 / x;
                if (y != x && cnt2.contains(y))
                    ans += cnt2[y];
            }
        }
        return ans;
    }
};

// 方法二：与方法一类似，我们也可以找出 nums2[j]*k 的所有倍数 （检查是否小于等于 max(nums1) 以降低时间复杂度），时间复杂度为 O( U/(nums2[j]*k) )，
// 注意到，与方法一的时间复杂度中 nums1[i] 位于分子不同，这次 nums2[j] 位于分母中，
// 我们可以预感到时间复杂度应该会变小。
// 最坏情况下，每个 nums2[j] 都不同，且这些数应该尽可能小（故可假设是 1~m ），
// 故遍历 nums2 找倍数的总时间复杂度为 U/k * sum{1/1, 1/2,..., 1/m} ，
// 这是调和级数求和，收敛于 U/k * ln(m) ，是自然对数，但是我们求时间复杂度对于对数的底是什么并不关系，
// 可以直接记作 O(U/k * logm) 。
// 思考：U/k * logm 与 m 哪个大？
// 我们之前忘记提到一个点，我们原本的目的是找 nums2[j]*k 的所有倍数，如果 U < nums2[j]*k ，那么就不会计入到调和级数的项中
// 也就是我们假设了 U/(nums2[j]*k) ≥ 1 ，
// 所以 U/k * logm ≥ m 。
// 为了进一步降低时间复杂度，因为 nums2 中会有重复的数，我们用哈希表统计其频次，以去重。
// 同样，对于 nums1 中的每个数用哈希表寻找其频次。
// 总时间复杂度 O(n + m + U/k * logm) 。
namespace solution_2
{
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, int> cnt1;
        unordered_map<long long, int> cnt2;
        for (int num : nums1) {
            cnt1[num]++;
        }
        for (int num : nums2) {
            cnt2[static_cast<long long>(num) * k]++;
        }
        long long ans = 0;
        // int max1 = ranges::max_element(nums1.begin(), nums1.end());
        int max1 = ranges::max(nums1);
        for (auto [x, c] : cnt2) {
            // 求 num2*k 的所有倍数
            for (long long y = x; y <= max1; y+= x) {
                if (cnt1.contains(y)) {
                    ans += static_cast<long long>(cnt1[y]) * c;
                }
            }
        }
        return ans;
    }
};
} // namespace solution_2

// @lc code=end

void test1() {
    vector<int> nums1 = {1,2,4,12};
    vector<int> nums2 = {2,4};
    int k = 3;

    Solution sol;
    int ans = sol.numberOfPairs(nums1, nums2, k);

    cout << ans << endl;
}

int main() {
    test1();

    return 0;
}