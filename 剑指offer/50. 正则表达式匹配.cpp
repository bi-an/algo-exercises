//https://www.cnblogs.com/AndyJee/p/4700373.html
/*
题目：
请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配
思路：
假设字符串为str，模式串为pattern，考虑以下情况：
A. 模式串下一个字符为*，即*(pattern+1)=='*'：
如果当前字符匹配，即*str=*pattern或者*str='.' && *pattern!='\0'，三种可能：
 1、模式串当前字符出现0次，即*表示当前字符出现0次，则str=str,pattern=pattern+2;
 2、模式串当前字符出现1次，即*表示当前字符出现1次，则str=str+1,pattern=pattern+2;
 3、模式串当前字符出现2次或2次以上，即*表示当前字符出现2次或以上，则str=str+1,pattern=pattern;
如果当前字符不匹配，则只能让*表示当前字符出现0次，则str=str，pattern=pattern+2;
B. 模式串下一个字符不为*
如果当前字符匹配，即*str=*pattern或者*str='.' && *pattern!='\0'，则str=str+1,pattern=pattern+1.
*/

class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if(str==NULL || pattern==NULL)
            return false;
        return matchCore(str,pattern); 
    }
     
    bool matchCore(const char* str,const char* pattern){
        if(*str=='\0' && *pattern=='\0')
            return true;
        if(*str!='\0' && *pattern=='\0')
            return false;
         
        if(*(pattern+1)=='*'){
            if(*str==*pattern || (*str!='\0' && *pattern=='.'))
                return matchCore(str,pattern+2)||matchCore(str+1,pattern+2)||matchCore(str+1,pattern);
            else
                return matchCore(str,pattern+2);
        }
         
        if(*str==*pattern || (*str!='\0' && *pattern=='.'))
            return matchCore(str+1,pattern+1);
         
        return false;
    }
};


//推荐写法。对于情况多而复杂的问题，用递归。
class Solution {
public:
    bool match(char* str, char* pattern)
    {
        if (str == nullptr || pattern == nullptr) return false;
        return matchCore(str, pattern);
    }

    bool matchCore(const char *str, const char *pattern) {
        if (pattern[0] == '\0') 
            return str[0] == '\0';
        bool firstMatch = (str[0] != '\0' && (str[0] == pattern[0] || pattern[0] == '.'));
        if (pattern[1] == '*') {
            return matchCore(str, pattern + 2) || (firstMatch && matchCore(str + 1, pattern));
        }
        else {
            return firstMatch && matchCore(str + 1, pattern + 1);
        }
    }
};


//法2：动态规划（递归）
