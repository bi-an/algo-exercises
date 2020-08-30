#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int findMaxLength(vector<int> &nums) {
    map<int, int> hash;
    int count = 0, maxLen = 0;

    hash.emplace(0, -1);

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 0)
        count--;
      else
        count++;
      auto itr = hash.find(count);
      if (itr != hash.end()) {
        int len = i - itr->second;
        if (len > maxLen)
          maxLen = len;
      } else {
        hash.emplace(count, i);
      }
    }

    return maxLen;
  }
};


