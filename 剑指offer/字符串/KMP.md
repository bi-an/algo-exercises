https://www.bilibili.com/video/BV1i64y1M7zv/?spm_id_from=333.788.videocard.2



next数组：
下标：
值：最长匹配的长度，最长匹配子串的下一个下标，模式串前缀和后缀的匹配长度。

双指针：i 自然下标，



https://zh.m.wikipedia.org/wiki/KMP%E7%AE%97%E6%B3%95

```cpp
#include <bits/stdc++.h>
using namespace std;

// fill the KMP table in T.
// T[j] 记录的是前缀和后缀匹配的最大长度。
// 当主串 m[i] 和模式串 w[j] 不匹配时：
// （1）如果 T[j]>=0，那么 j=T[j]；
// （2）如果 T[j]==-1，那么 i=i+1。
void kmp_table(string& w, vector<int>& T) {
    assert(w.length() == T.size());
    int pos = 2; // 前缀在 w 中的下标
    int cnd = 0; // T 下标
    T[0] = -1, T[1] = 0;
    while (pos < w.length()) {
        if (w[pos - 1] == w[cnd]) {
            cnd = cnd + 1;
            T[pos] = cnd; // 更新 T
            pos = pos + 1;
        } else if (cnd > 0) {
            cout << "pos=" << pos << ", cnd=" << cnd << ", T[cnd]=" << T[cnd] << endl;
            // cnd 后退直至 w[pos-1]==w[cnd] 或 cnd == 0
            // 也就是尝试缩短前缀长度，直至找到前后缀能匹配的长度
            cnd = T[cnd];
        } else {
            T[pos] = 0; // 更新 T
            pos = pos + 1;
        }
    }
}

void kmp_table_unittest() {
    string w = "ABCABCABDE";
    vector<int> T(w.length());
    kmp_table(w, T);
    for (int i = 0; i < T.size(); ++i) {
        cout << i << "\t";
    }
    cout << endl;
    for (int i = 0; i < T.size(); ++i) {
        cout << w[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < T.size(); ++i) {
        cout << T[i] << "\t";
    }
    cout << endl;
}

int main() {
    kmp_table_unittest();


    return 0;
}

```