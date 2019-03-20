class Solution {
public:
	int FirstNotRepeatingChar(string str) {
		if (str.empty()) return -1;
		const int tableSize = 256; //由于char类型是8bit，所以一共可以表示256个字符
		unsigned int hashTable[tableSize] = {0};
		for (size_t i = 0; i < str.size(); i++) {
			hashTable[str[i]]++;
		}
		for (int i = 0; i < str.length(); i++) {
			if (hashTable[str[i]] == 1)
				return i;
		}
		return -1;
	}
};

