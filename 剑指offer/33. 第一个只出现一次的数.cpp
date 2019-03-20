class Solution {
public:
	int FirstNotRepeatingChar(string str) {
		if (str.empty()) return -1;
		const int tableSize = 256;
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