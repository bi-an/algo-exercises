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

// 双指针，分别从左和从右遍历
class Solution {
public:
    string reverseVowels(string s) {
        int n = s.size();
        int left = 0, right = n - 1;
        while (left < right) {
            while (left < n && !isVowel(s[left])) left++;
            while (right >= 0 && !isVowel(s[right])) right--;
            if (/*left < n && right >= 0 &&*/ left <= right) {
                std::swap(s[left], s[right]);
                left++, right--;
            }
        }
        return s;
    }

    bool isVowel(char c) {
        string vowels = "aeiouAEIOU";
        return vowels.find(c) != std::string::npos;
    }
};

// 写法二，和上面代码本质一样
namespace solution_2 {

class Solution {
public:
    string reverseVowels(string s) {
        // cpp中，后缀's'表示一个string类型的字面值常量
        // 使用捕获列表的好处是，即使多次调用lambda函数也只会初始化一次，
        // 并且在lambda函数内部不可变
        // 捕获列表的生存期与lambda对象相同，其存储在lambda对象的stack上
        auto isVowel = [vowels = "aeiouAEIOU"s](char c) -> bool {
            return vowels.find(c) != string::npos;
        };
        int l = 0, r = (int)s.length() - 1;
        while (l < r) {
            if (isVowel(s[l]) && isVowel(s[r])) {
                swap(s[l], s[r]);
                ++l;
                --r;
            } else {
                if (!isVowel(s[l]))
                    ++l;
                else
                    --r;
            }
        }
        return s;
    }
};

}  // namespace solution_2
