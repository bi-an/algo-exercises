// @ref labuladong
// 分治法
// 备忘录：比如 1+1+1+1+1
//      则 (1+1)+(1+1+1)
//      和 (1+1+1)+(1+1) 会计算重复，此时直接从备忘录中取出结果就可以了
class Solution {
public:
	vector<int> diffWaysToCompute(string input) {
		vector<int> res;
		// 备忘录剪枝（也可以不用备忘录）
		if(memo.find(input) != memo.end())
            return memo[input];

		for (int i = 0; i < input.length(); i++) {
			char c = input[i];
			if (c == '+' || c == '-' || c == '*') {
				vector<int> left = diffWaysToCompute(input.substr(0, i)); // 子串的运算结果可能有多个（括号加在不同位置）
				vector<int> right = diffWaysToCompute(input.substr(i + 1, input.length() - i - 1));
				for (int a : left) {
					for (int b : right) {
						switch (c) {
						case '+':
							res.push_back(a + b);
							break;
						case '-':
							res.push_back(a - b);
							break;
						case '*':
							res.push_back(a * b);
							break;
						}
					}
				}
			}
		}

        // 如果res为空，说明input中没有运算符，它是一个数
		if (res.empty())
			res.push_back(atoi(input.c_str()));
        
        // 添加进备忘录
        memo[input] = res;
		return res;
	}

private:
	map<string, vector<int>> memo;
};