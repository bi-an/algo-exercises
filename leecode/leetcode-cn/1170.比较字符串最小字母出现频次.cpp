/*
 * @lc app=leetcode.cn id=1170 lang=cpp
 *
 * [1170] 比较字符串最小字母出现频次
 */

// 排序 + 二分
// 时间复杂度：O(p(n+m)logn)，其中 p 是 words[i], queries[j] 的最大长度
// 空间复杂度：O(n)
class Solution {
    // 写法一
    int f1(string& s) {
        // unordered_map<int, int> freq;
        vector<int> freq(26);  // 全是英文小写字母
        int mi = 'z';
        for (char c : s) {
            int idx = c - 'a';
            ++freq[idx];
            mi = min(mi, idx);
        }
        return freq[mi];
    }

    // 写法二
    int f(string& s) {
        char mi = 'z';
        int cnt = 0;
        for (char c : s) {
            if (c < mi) {
                mi = c;
                cnt = 1;
            } else if (c == mi) {
                ++cnt;
            }
        }
        return cnt;
    }

public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        int n = words.size(), m = queries.size();
        vector<int> fw(n), ans(m);
        for (int i = 0; i < n; ++i)
            fw[i] = f(words[i]);
        ranges::sort(fw);

        int i = 0;
        for (auto& s : queries) {
            int j = ranges::upper_bound(fw, f(s)) - fw.begin();
            ans[i++] = n - j;
        }

        return ans;
    }
};

namespace solution_2 {

// @lc code=start
// 官方题解：https://leetcode.cn/problems/compare-strings-by-frequency-of-the-smallest-character/solutions/2297291/bi-jiao-zi-fu-chuan-zui-xiao-zi-mu-chu-x-pb50/
// 我们需要在 words 中找出 f(W) > f(queries[i]) 的所有 W 的数目（即 f(W) 的数目）
// 哈希表（计数） + 后缀和
// 时间复杂度：O(p(n+m))
// 空间复杂度：O(1) ，只用了常数空间。
class Solution {
    int f(string& s) {
        char mi = 'z';
        int cnt = 0;
        for (char c : s) {
            if (c < mi) {
                mi = c;
                cnt = 1;
            } else if (c == mi) {
                ++cnt;
            }
        }
        return cnt;
    }

public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        int m = queries.size(), n = words.size();
        vector<int> ans(m);

        // 对 f(W) 计数
        // 因为 W.length ≤ 10 ，所以 f(W) ≤ 10
        int cnt[12]{};
        for (string& w : words)
            cnt[f(w)]++;

        // 后缀和，即 f(W) ≥ 某值 的个数
        for (int i = 10; i >= 0; --i)
            cnt[i] += cnt[i + 1];

        int i = 0;
        for (string& s : queries)
            ans[i++] = cnt[f(s) + 1];  // 题意要严格大于

        return ans;
    }
};
// @lc code=end

}  // namespace solution_2
