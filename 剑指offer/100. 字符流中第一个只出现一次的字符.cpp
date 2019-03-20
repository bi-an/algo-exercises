class Solution
{
public:
	Solution() :index(0) {
		for (int i = 0; i < 256; i++)
			occurence[i] = -1;
	}
	//Insert one char from stringstream
	void Insert(char ch)
	{
		if (occurence[ch] == -1)
			occurence[ch] = index;
		else if (occurence[ch] >= 0)
			occurence[ch] = -2;
		++index;
	}
	//return the first appearence once char in current stringstream
	char FirstAppearingOnce()
	{
		char ch = '#';
		int minIndex = std::numeric_limits<int>::max();
		for (int i = 0; i < 256; i++) {
			if (occurence[i] >= 0 && occurence[i] < minIndex) {
				ch = (char)i;
				minIndex = occurence[i];
			}
		}
		return ch;
	}

private:
	// occurence[i]: i表示字符的ascii码
	// occurence[i]=-1: 该字符没有出现
	// occurence[i]=-2: 该字符不止出现一次
	// occurence[i]>=0: 该字符只出现了一次
	int occurence[256];
	int index; //记录字符流的下个位置

};


// 测试代码
int main() {
	
	Solution sol;
	string str = "google";
	for (int i = 0; i < str.size(); i++) {
		sol.Insert(str[i]);
		cout << sol.FirstAppearingOnce() << " ";
	}

	return 0;
}