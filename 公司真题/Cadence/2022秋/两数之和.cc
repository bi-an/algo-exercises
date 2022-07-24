// 姻缘配
// 从输入的数字中，找出两个相加之和为 m 的两个数。计算这样的匹配对的个数。
// 不同下标的数视为不同，即使它们数值上相等。

#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, y;
    cin >> x;
    string num = to_string(x);
    if (x < 0) {
        int i = 1;
        for (; i < num.size(); ++i) {
            if (num[i] > '6')
                break;
        }
        cout << num.substr(0, i) + "6" + num.substr(i, num.size() - i) << endl;
    } else {
        int i = 0;
        for (; i < num.size(); ++i) {
            if (num[i] < '6')
                break;
        }
        cout << num.substr(0, i) + "6" + num.substr(i, num.size() - i) << endl;
    }
    
    
}