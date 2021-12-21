// @Athor zzg
class Solution {
    public String intToRoman(int num) {
        String[] tens = {"I", "X", "C", "M"};
        String[] fives = {"V", "L", "D"};

        int count, i = 3, ten = 1000;
        String ans = new String();

        while(num > 0 && i >= 0 && ten > 0) {
            count = num / ten;
            num = num % ten;
            switch (count) {
                case 0:
                    break;
                case 1:
                case 2:
                case 3:
                    for(int j=0;j<count;j++)
                        ans += tens[i];
                    break;
                case 4:
                    ans += tens[i] + fives[i];
                    break;
                case 5:
                    ans += fives[i];
                    break;
                case 6:
                case 7:
                case 8:
                    ans += fives[i];
                    count = count % 5;
                    for(int j=0;j<count;j++)
                        ans += tens[i];
                    break;
                case 9:
                    ans += tens[i] + tens[i + 1];
                    break;
                default:
                    break;
            }
            i--;
            ten /= 10;
        }

        return ans;
    }
}

// 官方题解：模拟法
class Solution {
    public String intToRoman(int num) {
        int[] values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        String[] symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < values.length; i++) {
            while (num - values[i] >= 0) {
                num -= values[i];
                sb.append(symbols[i]);
            }
        }

        return sb.toString();
    }
}

// 官方题解二：硬编码
// 类似ascii码表，查表得到答案
class Solution {
    String[] thousands = {"", "M", "MM", "MMM"};
    String[] hundreds  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    String[] tens      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    String[] ones      = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    public String intToRoman(int num) {
        StringBuffer roman = new StringBuffer();
        roman.append(thousands[num / 1000]);
        roman.append(hundreds[num % 1000 / 100]);
        roman.append(tens[num % 100 / 10]);
        roman.append(ones[num % 10]);
        return roman.toString();
    }
}

// 作者：LeetCode-Solution
// 链接：https://leetcode-cn.com/problems/integer-to-roman/solution/zheng-shu-zhuan-luo-ma-shu-zi-by-leetcod-75rs/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。