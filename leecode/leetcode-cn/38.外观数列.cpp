// 遍历生成
// 时间复杂度O(N*M)，N=n, M为最长遍历过程中的最长字符串
// 空间复杂度O(N*M)，压栈空间；如果改成循环，空间复杂度为O(M)
class Solution {
public:
    string countAndSay(int n) {
        return countAndSay("1", n);
    }

    // 遍历生成
    string countAndSay(string cur, int depth) {
        if (depth == 1)
            return cur;
        string next;
        char c = cur[0];
        int cnt = 1;
        for (int i = 1; i < cur.length(); i++) {
            if (c == cur[i]) {
                cnt++;
            }
            else {
                next += to_string(cnt) + c;
                cnt = 1;
                c = cur[i];
            }
        }
        next += to_string(cnt) + c;
        return countAndSay(next, --depth);
    }
};