#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isStrobogrammatic(string num) {
    map<char, char> table{
        {'0', '0'}, {'1', '1'}, {'6', '9'}, {'8', '8'}, {'9', '6'},
    };

    int left = 0, right = num.length() - 1;
    while (left <= right) {
      // 如果字母不存在映射或映射不对，则返回假
      if (!table.count(num[right]) || table[left] != num[right]) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }
};