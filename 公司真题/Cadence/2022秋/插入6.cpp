// 给定一个数字，在其中插入一个数字6，使之成为最大的整数。

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