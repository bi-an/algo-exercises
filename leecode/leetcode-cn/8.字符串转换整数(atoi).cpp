#include "bits/stdc++.h"
using namespace std;

class Solution {
 public:
  int myAtoi(string s) {
    long res = 0;
    int flag = 1;
    int i, n = s.size();
    for (i = 0; i < n; i++) {
      if (s[i] == '-') {
        flag = -1;
      }
      if (s[i] == '+' || s[i] == '-') {
        i++;
        break;
      } else if (s[i] - '1' >= 0 && s[i] - '9' <= 0 || s[i] != ' ') {
        break;
      }
    }
    for (; i < n; i++) {
      if (s[i] - '0' < 0 || s[i] - '9' > 0) break;
      long tmp = res * 10 + (s[i] - '0');
      if (flag * tmp >= INT_MAX) {
        res = INT_MAX;
        break;
      } else if (flag * tmp <= INT_MIN) {
        res = INT_MIN;
        break;
      }
      res = tmp;
    }
    return flag * res;
  }
};

// 对于这种条件情况过多的问题，直接写代码容易冗长，可以使用“自动机”
// 参考官方题解
// Tip: 判断是否溢出，可以反向思考，INT_MAX/10与当前值的比较
class Solution {
  enum States { START, SIGNED, IN_NUMBER, END };

  unordered_map<States, vector<States>> states = {
      {START, {START, SIGNED, IN_NUMBER, END}},
      {SIGNED, {END, END, IN_NUMBER, END}},
      {IN_NUMBER, {END, END, IN_NUMBER, END}},
      {END, {END, END, END, END}}};

  int getCol(char c) {
    if (isspace(c))
      return 0;
    else if (c == '+' || c == '-')
      return 1;
    else if (isdigit(c))
      return 2;
    else
      return 3;
  }

 public:
  int myAtoi(string s) {
    long long res = 0;
    States state = START;
    int flag = 1;
    for (char c : s) {
      state = states[state][getCol(c)];
      if (state == END)
        break;
      else if (state == SIGNED && c == '-')
        flag = -1;
      else if (state == IN_NUMBER) {
        res = 10 * res + (c - '0');
        res = flag > 0 ? min((long long)INT_MAX, res)
                       : min(-(long long)INT_MIN, res);
      }
    }
    return flag * res;
  }
};