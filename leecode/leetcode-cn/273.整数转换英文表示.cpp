class Solution {
public:
    string ones[10] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
    string teens[10] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
    string tens[10] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    string thousands[4] = { " Billion", " Million", " Thousand", ""}; // 这里处理空格（也可以通过string::pop_back()去除尾部空格）

    string numberToWords(int num) {
        string ans;
        if (num == 0)
            return "Zero";
        for (int i = 1000000000, j = 0; i > 0 && num > 0; i /= 1000, j++) {
            int cur = num / i;
            num %= i;
            if (cur > 0) {
                ans += recursion(cur) + thousands[j];
                if (num > 0) {
                    ans += " ";
                }
            }
        }
        return ans;
    }

    string recursion(int num) {
        string str;
        if (num < 20) {
            str = num < 10 ? ones[num] : teens[num % 10];
        }
        else if (num < 100) {
            str = tens[num / 10];
            num %= 10;
            if (num > 0) {
                str += " " + recursion(num);
            }
        }
        else {
            str = ones[num / 100] + " Hundred";
            num %= 100;
            if (num > 0) {
                str += " " + recursion(num);
            }
        }
        return str;
    }
};