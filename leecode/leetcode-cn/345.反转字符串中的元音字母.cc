/**
给你一个字符串 s ，仅反转字符串中的所有元音字母，并返回结果字符串。

元音字母包括 'a'、'e'、'i'、'o'、'u'，且可能以大小写两种形式出现。

 
示例 1：

输入：s = "hello"
输出："holle"
示例 2：

输入：s = "leetcode"
输出："leotcede"
 

提示：

1 <= s.length <= 3 * 105
s 由 可打印的 ASCII 字符组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-vowels-of-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    string reverseVowels(string s) {
        int n = s.size();
        int left = 0, right = n - 1;
        while(left < right) {
            while(left < n && !isVowel(s[left])) left++;
            while(right >= 0 && !isVowel(s[right])) right--;
            if(/*left < n && right >= 0 &&*/ left <= right) {
                std::swap(s[left], s[right]);
                left++, right--;
            }
        }
        return s;
    }

    bool isVowel(char c) {
        string vowels = "aeiouAEIOU";
        for(char cc : vowels) {
            if(cc == c) return true;
        }
        return false;
    }
};