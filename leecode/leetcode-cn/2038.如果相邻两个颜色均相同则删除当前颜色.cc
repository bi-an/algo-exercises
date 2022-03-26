/*
 * @Author: your name
 * @Date: 2022-03-26 17:22:48
 * @LastEditTime: 2022-03-26 17:23:25
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: \practice\leecode\leetcode-cn\如果相邻两个颜色均相同则删除当前颜色.cc
 */


class Solution {
public:
    bool winnerOfGame(string colors) {
        int freq[2] = {0, 0};
        char cur = 'C';
        int cnt = 0;
        for(char c : colors) {
            if(c != cur) {
                cur = c;
                cnt = 1;
            } else {
                ++cnt;
                if(cnt >= 3)
                    ++freq[c - 'A'];
            }
        }
        return freq[0] > freq[1];
    }
};


// 写法二
class Solution {
public:
    bool winnerOfGame(string colors) {
        int ansA = 0, ansB = 0;
        int cntA = 0, cntB = 0;
        for(char c : colors) {
            if (c == 'A') {
                ++cntA;
                ansB += (cntB - 2) > 0 ? (cntB - 2) : 0;
                cntB = 0;
            } else {
                ++cntB;
                ansA += (cntA - 2) > 0 ? (cntA - 2) : 0;
                cntA = 0;
            }
        }
        ansA += (cntA - 2) > 0 ? (cntA - 2) : 0;
        ansB += (cntB - 2) > 0 ? (cntB - 2) : 0;
        return ansA > ansB;
    }
};