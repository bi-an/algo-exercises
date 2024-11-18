class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0")
            return "0";
        int m = num1.size(), n = num2.size();
        vector<int> digits(m + n); // 默认初始化为 0
        for (int i = m - 1; i >= 0; --i) {
            int carry = 0;
            int x = num1[i] - '0';
            for (int j = n - 1; j >= 0; --j) {
                int y = num2[j] - '0';
                // 任何一次加法都可能导致结果大于 10
                int cur = x * y + carry + digits[i + j + 1];
                digits[i + j + 1] = cur % 10; 
                carry = cur / 10;
            }
            digits[i] += carry;
        }

        string ans;
        int i = 0;
        while (i <= m + n - 1 && digits[i] == 0)
            ++i;
        while (i <= m + n - 1) {
            ans += digits[i++] + '0';
        }
        return ans;
    }
};