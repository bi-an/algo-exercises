class Solution {
public:
    int compareVersion(string version1, string version2) {
        int left1 = 0, left2 = 0;
        int n1 = version1.length(), n2 = version2.length();
        while(left1 < n1 || left2 < n2) {
            int right1 = left1, right2 = left2;
            while(right1 < n1 && version1[right1] != '.')
                right1++;
            while(right2 < n2 && version2[right2] != '.')
                right2++;

            // cout << left1 << "," << right1 << ";" << left2 << "," << right2 << endl;
            int num1 = 0, num2 = 0;
            if(right1 > left1) 
                num1 = atoi(version1.substr(left1, right1 - left1).c_str());
            if(right2 > left2)
                num2 = atoi(version2.substr(left2, right2 - left2).c_str());
            // if(num1 > num2)
            //     return 1;
            // else if(num1 < num2)
            //     return -1;
            if(num1 != num2) 
                return num1 > num2 ? 1 : -1;
            left1 = right1 + 1; // 跳过点号
            left2 = right2 + 1;
        }
        return 0;
    }
};