// 方法一：模拟
// 时间复杂度：O(n)


// 方法二：数学推导
// 详见 "319.灯泡开关.md"
class Solution {
public:
    int bulbSwitch(int n) {
        return sqrt(n + 0.5); // 只要 delta 不超过 1 都可以，不一定是 0.5
    }
};