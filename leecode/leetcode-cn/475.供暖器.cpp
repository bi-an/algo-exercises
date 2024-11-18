// 方法一：排序 + 二分查找

// 方法二：排序 + 双指针
// 参见官方题解
class Solution {
 public:
  int findRadius(vector<int>& houses, vector<int>& heaters) {
    sort(houses.begin(), houses.end());
    sort(heaters.begin(), heaters.end());

    int ans = 0;
    for (int i = 0, j = 0; i < houses.size() && j < heaters.size(); i++) {
      while (j + 1 < heaters.size() &&
             abs(houses[i] - heaters[j]) >= abs(houses[i] - heaters[j + 1]))
        j++;
      ans = max(ans, abs(houses[i] - heaters[j]));
    }

    return ans;
  }
};