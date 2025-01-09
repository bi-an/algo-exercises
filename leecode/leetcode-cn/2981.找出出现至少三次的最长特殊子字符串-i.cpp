/*
 * @lc app=leetcode.cn id=2981 lang=cpp
 *
 * [2981] 找出出现至少三次的最长特殊子字符串 I
 */

// @author bi-an
// 二分查找 + 定长滑动窗口 + 双哈希表
// 时间复杂度：O(nlogn)
// 空间复杂度：O(|Σ|)，其中 |Σ| 为字符集长度。
class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();
        constexpr int N = 26;
        // occur[i] 窗口内字符（ i+'a' ）的计数
        // cnt[i] 由单一字符（ i+'a' ）构成的、长度等于窗口的子串，统计其“出现次数大于等于 3 次”的频次
        int occur[N], cnt[N];

        auto check = [&](int m) {
            bzero(occur, sizeof(occur));
            bzero(cnt, sizeof(cnt));
            for (int i = 0; i < m - 1; ++i) {
                ++occur[s[i] - 'a'];
            }

            for (int l = 0, r = m - 1; r < n; ++l, ++r) {
                if (++occur[s[r] - 'a'] == m)
                    ++cnt[s[r] - 'a'];
                --occur[s[l] - 'a'];
            }

            int k = 0;
            for (int i = 0; i < N; ++i) {
                if (cnt[i] >= 3)
                    return true;
            }
            return false;
        };

        int left = 1, right = n;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid))
                left = mid + 1;  // mid = left - 1 总是合法的
            else
                right = mid - 1;
        }

        return left - 1 > 0 ? left - 1 : -1;  // 或 right ，因为结束时 right 处于 left 左边
    }
};

namespace solution_2 {

// 二分查找 + 变长滑动窗口 + 单哈希表
// 题解：https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-i/solutions/2793908/python3javacgotypescript-yi-ti-yi-jie-er-8jhh/
// 时间复杂度：O(nlogn)
// 空间复杂度：O(|Σ|)，其中 |Σ| = 26 为字符集长度。
class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();

        auto check = [&](int m) {
            int cnt[26]{};  // 长度 26 ，每次构造也不会开销很大
            for (int l = 0; l < n;) {
                int r = l + 1;  // 或 r = l;
                while (r < n && s[l] == s[r])
                    r++;
                int k = s[l] - 'a';
                // 长度 len 的字符串有 len - (m - 1) 个长度为 m 的子串
                cnt[k] += max(0, r - l - m + 1);
                if (cnt[k] >= 3)
                    return true;
                l = r;
            }
            return false;
        };

        int left = 1, right = n;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (check(mid))
                left = mid + 1;
            else
                right = mid - 1;
        }

        return right <= 0 ? -1 : right;
    }
};

}  // namespace solution_2

namespace solution_3 {

// @lc code=start
// 字符串分割 + 哈希表 + 变长滑动窗口
// 题解：https://leetcode.cn/problems/find-longest-special-substring-that-occurs-thrice-i/solutions/2585837/fei-bao-li-zuo-fa-fen-lei-tao-lun-python-p1g2/
// 将相同字符组成的子串全部分组，例如 aabbbbaaacd 分割成：aa, bbbb, aaa, c, d
// 统计每组字符串的长度，按字符种类存入哈希表，按长度倒序排序，例如 cnt['a'] = {3, 2} ，cnt['b'] = {4} 。
// 遍历字符种类，从最长、次长、次次长中找出 3 个子串（如果有的话），选最优方案，记录最优值。
// （1）从最长中选 3 个子串：该子串最大长度为 len - 2 ；
// （2）从最长和次长中选 3 个子串：该子串最大长度为：
//      a. 如果最长和次长的长度相同：该子串最大长度为 len1 - 1 ；
//      b. 如果最长大于次长的长度：该子串的最大长度为 len2 （即次长的长度）；
//      合并两种情况，该子串最大长度为 min(len1 - 1, len2) 。
//      因为第一种情况中，len1 = len2 >= len1 - 1 ，min(len1 - 1, len2) = len1 - 1 ；
//      第二种情况中，len1 - 1 >= len2 ，min(len1 - 1, len2) = len2 .
//      定性分析可知，主要由次长的长度决定。
//  （3）从最长、次长、次次长中各选一个：该子串最大长度为 len3 ，都选次次长即可。
// 这三种情况，选最大值，记录。
//
// 时间复杂度：O(nlogn)，时间瓶颈在于排序；如果用堆维护前 3 大可以做到 O(n) 。
// 空间复杂度：O(n)
class Solution {
public:
    int maximumLength(string s) {
        int n = s.length();

        vector<int> groups[26];
        int cnt = 0;  // 本质也是变长滑动窗口，也可以用双指针
        for (int i = 0; i < n; ++i) {
            ++cnt;
            if (i + 1 == n || s[i] != s[i + 1]) {
                groups[s[i] - 'a'].push_back(cnt);
                cnt = 0;  // 下一次重新统计
            }
        }

        int ans = 0;  // 长度
        for (auto& g : groups) {
            if (g.empty())
                continue;
            ranges::sort(g, greater<int>());  // TODO: 为什么 greater() 不加模板参数也行
            // 在 g 末尾添加两个 0 ，防止 g[1] 和 g[2] 越界
            g.push_back(0);
            g.push_back(0);
            ans = max({ans, g[0] - 2, min(g[0] - 1, g[1]), g[2]});
        }

        return ans ? ans : -1;  // 根据题意，长度为 0 表示没有找到，此时应该返回 -1 .
    }
};
// @lc code=end

}  // namespace solution_3
