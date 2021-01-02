class Solution
{
 public:
  int FirstNotRepeatingChar(string str)
  {
    if (str.empty())
      return -1;
    const int tableSize = 256; //由于char类型是8bit，所以一共可以表示256个字符
    unsigned int hashTable[tableSize] = { 0 };
    for (size_t i = 0; i < str.size(); i++)
    {
      hashTable[str[i]]++;
    }
    for (int i = 0; i < str.length(); i++)
    {
      if (hashTable[str[i]] == 1)
        return i;
    }
    return -1;
  }
};

// 相关题目：
// 1. 若要考虑string中有汉字的情况，怎么解决？
//	  TODO
//
// 2. 输入两个字符串，删除第一个字符串在第二个字符串中出现的字符。
//	  思路：把第二次字符串的字符存入hash表。
//
// 3. 删除字符串中所有重复出现的字符。
//    思路：boolean类型hash表，下标为ascii，初值false。依次扫描字符串，并查hash表，如果是false，就赋值为true；如果true，就从字符串中删掉这个字符。
//
// 4. 在英语中，如果两个单词中出现的字母相同，且这些字母出现频次也相同个，那么互为变位词(Anagram)。
//    判断两个字符串是不是互为变位词。
//    思路：hash表存放每个字符出现的次数。扫描第一个字符串时，统计次数；扫描第二个字符串时，不断减少出现的字符的频次。
//	  最后，如果hash表中所有值都是0，那么它们互为变位词。
