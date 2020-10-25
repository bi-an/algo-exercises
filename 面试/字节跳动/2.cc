#include <iostream>
//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool cmp(string& s1, string& s2){
    int len = min(s1.length(),s2.length());
    int maxLen = max(s1.length(),s2.length());
    int i=0;
    for(;i<len && s1[i]==s2[i];i++);
    if(i==len)
        if(s1.length() > s2.length()) 
        {
            if(s1[i]=='0')
                return false;
        }
        else if(s1.length() < s2.length()) 
        {
            if(s2[i]=='0')
                return true;
        }
    return s1[i]>s2[i];
}

int fun(vector<int>& nums){
    vector<string> vec(nums.size());
    for(int i=0;i<vec.size();i++){
        vec[i] = to_string(nums[i]);
    }
    //sort(vec.begin(),vec.end(), greater<string>());
    sort(vec.begin(),vec.end(), cmp);
    string str;
    for(int i=0;i<vec.size();i++){
        str+=vec[i];
    }
    return atoi(str.c_str());
}

int main() {
    //int a;
    //cin >> a;
    vector<int> vec = {3,30,34,5,8};
    cout << fun(vec) << endl;
    
    //cout << "Hello World!" << endl;
}