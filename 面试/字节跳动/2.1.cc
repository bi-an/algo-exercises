/**
 * 给定一组正整数，重新排列它们的顺序然后组成一个最大的整数
 * 输入: [11,5] 输出: 511
 * 
 * 输入: [3,30,34,5,8] 输出: 8534330
 * 
*/

// 提示：与其对cmp特殊处理，不如直接将两个数结合起来比较一下，比如3和30，330 > 303.

#include <iostream>
//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool cmp(int a, int b){
    string s1 = to_string(a), s2 = to_string(b);
    int num1 = atoi((s1+s2).c_str());
    int num2 = atoi((s2+s1).c_str());
    return num1 > num2;
}

int maxInt(vector<int>& vec){
    sort(vec.begin(), vec.end(), cmp);
    string str;
    for(int i=0;i<vec.size();i++){
        str+=to_string(vec[i]);
    }
    return atoi(str.c_str());
}

int main(){

    vector<int> vec = {3,30,34,5,8};
    vector<int> vec2 = {30, 304};
    cout << maxInt(vec) << endl;
    cout << maxInt(vec2) << endl;

    return 0;
}