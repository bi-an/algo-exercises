#include "bits/stdc++.h"
using namespace std;

// 方法一：拒绝采样
// 随机生成x和y，也就是正方形。一直采样，直到(x,y)落在圆内为止。
// 时间复杂度：O(1)，最坏O(∞)
class Solution {
  // TODO 有一个奇特的问题
  // 这里的{}都不能改成()，否则会编译报错
  mt19937 g{random_device{}()};
  uniform_real_distribution<double> uni{0, 1};
  double r, xc, yc;

 public:
  Solution(double radius, double x_center, double y_center) {
    r = radius;
    xc = x_center;
    yc = y_center;
  }

  vector<double> randPoint() {
    while (true) {
      double x = uni(g) * 2 * r - r + xc;
      double y = uni(g) * 2 * r - r + yc;
      if (pow(x - xc, 2) + pow(y - yc, 2) < pow(r, 2)) return {x, y};
    }
  }
};

// 方法二：随机分布函数（概率密度函数）证明
// 这里只记下结论，证明过程见官方题解
// 
// 产生两个随机数，一个半径，一个角度
// 关键在于，我们能够保证角度等概率产生，但是不能保证半径随机产生时，落在圆内概率均等
// 假设单位圆内，有2个比它小的圆O1和O2，其中，R1<R2.
// 那么点落在O1和O2圆周上的概率应该与其圆周长成正比。
// 
// 结论是：随机变量R = sqrt([0,1]均匀分布)*r
class Solution {
    mt19937 g{random_device{}()};
    uniform_real_distribution<double> uni{0,1};
    double r, xc, yc;
public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        xc = x_center;
        yc = y_center;
    }
    
    vector<double> randPoint() {
        double theta = uni(g) * 2 * M_PI;
        double R = sqrt(uni(g)) * r;
        return {xc + R*cos(theta), yc + R*sin(theta)};
    }
};