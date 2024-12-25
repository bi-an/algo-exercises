/*
 * @lc app=leetcode.cn id=3306 lang=cpp
 *
 * [3306] 元音辅音字符串计数 II
 */

#include <bits/stdc++.h>
using namespace std;

// 题解：https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
// 写法一
namespace version_1 {

class Solution {
    struct Window {
        unordered_map<char, int> vowels;
        int consonants = 0;
        // const string VOWELS = "aeiou";

        bool isVowel(char c) {
            // return VOWELS.find(c) != string::npos;
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        }

        void push(char c) {
            if (isVowel(c))
                vowels[c]++;
            else
                consonants++;
        }

        void pop(char c) {
            if (isVowel(c)) {
                if (--vowels[c] == 0)
                    vowels.erase(c);
            } else {
                --consonants;
            }
        }

        int numVowels() {
            return vowels.size();
        }

        int numConsonants() {
            return consonants;
        }
    };

public:
    long long countOfSubstrings(string word, int k) {
        long long ans = 0;
        int n = word.length();
        Window w1, w2;
        for (int l1 = 0, l2 = 0, r = 0; r < n; ++r) {
            w1.push(word[r]);
            w2.push(word[r]);
            // 窗口缩短到第一个严格小于 k 位置
            while (w1.numVowels() == 5 && w1.numConsonants() >= k)
                w1.pop(word[l1++]);
            // 窗口缩短到第一个严格小于 k + 1 位置（也就是等于 k 处）
            // 判定条件也可以写成 w2.numConsonants() >= k + 1
            while (w2.numVowels() == 5 && w2.numConsonants() > k)
                w2.pop(word[l2++]);
            // 窗口外都合法，即 [0..(left-1), right]
            ans += l1 - l2;  // 差集
        }
        return ans;
    }
};

}  // namespace version_1

// 题解：https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/
// 写法二
namespace version_2 {

class Solution {
    // const string VOWELS = "aeiou";

    bool isVowel(char c) {
        // return VOWELS.find(c) != string::npos; // 效率低很多
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    // 元音至少各有一个、辅音个数 ≥ k 的子字符串个数
    // 反过来，求“元音至少各有一个、辅音个数 ≤ k” 的个数也行，做法类似，具体可参考「992.k-个不同整数的子数组」
    long long f(string& word, int k) {
        long long ans = 0;
        unordered_map<char, int> cnt1;    // 元音
        int n = word.length(), cnt2 = 0;  // 辅音

        for (int l = 0, r = 0; r < n; ++r) {
            char c = word[r];
            if (isVowel(c))
                cnt1[c]++;
            else
                cnt2++;
            // 窗口缩小到恰好严格小于 k 的位置
            while (cnt1.size() == 5 && cnt2 >= k) {
                c = word[l++];
                if (isVowel(c)) {
                    if (--cnt1[c] == 0)
                        cnt1.erase(c);
                } else {
                    --cnt2;
                }
            }
            ans += l;  // 比当前大的窗口 [0...(left-1), right] 都是合法的
        }

        return ans;
    }

public:
    long long countOfSubstrings(string word, int k) {
        // 大于等于 k 的集合
        // 大于等于 k + 1 的集合，即大于 k 的集合
        // 二者差集
        return f(word, k) - f(word, k + 1);
    }
};

}  // namespace version_2

// @lc code=start
// 题解：https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/solutions/2934309/liang-ci-hua-chuang-pythonjavacgo-by-end-2lpz/
// 写法三
// 将哈希表直接改成数组，效率会高一倍
// TODO: 判断元音的代码可以用位运算优化，把 aeiou 视作集合 {0,4,8,14,20}，根据 从集合论到位运算，这等于 1065233。用 (1065233 >> b & 1) > 0 可以判断字母 b 是否为元音。
class Solution {
    // const string VOWELS = "aeiou";

    bool isVowel(char c) {
        // return VOWELS.find(c) != string::npos; // 效率低很多
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }

    // 如果不想浪费空间，用数组实现哈希表时，可以用 index() 生成哈希表中的下标，即 int cnt1[5]{}; int idx = cnt1[index(c)];
    // int index(char c) {
    //     switch (c) {
    //         case 'a':
    //             return 0;
    //         case 'e':
    //             return 1;
    //         case 'i':
    //             return 2;
    //         case 'o':
    //             return 3;
    //         case 'u':
    //             return 4;
    //     }
    //     return 5;
    // }

    // 元音至少各有一个、辅音个数 ≥ k 的子字符串个数
    long long f(string& word, int k) {
        long long ans = 0;
        int n = word.length();
        int cnt1[128]{}, size1 = 0;  // 元音
        int cnt2 = 0;                // 辅音

        for (int l = 0, r = 0; r < n; ++r) {
            char c = word[r];
            if (isVowel(c)) {
                if (cnt1[c]++ == 0)
                    size1++;
            } else {
                cnt2++;
            }
            // 窗口缩小到恰好严格小于 k 的位置
            while (size1 == 5 && cnt2 >= k) {
                c = word[l++];
                if (isVowel(c)) {
                    if (--cnt1[c] == 0)
                        --size1;
                } else {
                    --cnt2;
                }
            }
            ans += l;  // 比当前大的窗口 [0...(left-1), right] 都是合法的
        }

        return ans;
    }

public:
    long long countOfSubstrings(string word, int k) {
        // 大于等于 k 的集合
        // 大于等于 k + 1 的集合，即大于 k 的集合
        // 二者差集
        return f(word, k) - f(word, k + 1);
    }
};
// @lc code=end

using namespace version_2;
int main() {
    Solution sol;
    string word = "eoeaui";
    int k = 0;
    cout << sol.countOfSubstrings(word, k) << endl;

    return 0;
}