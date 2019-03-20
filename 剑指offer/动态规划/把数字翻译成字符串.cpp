// 面试题46：把数字翻译成字符串
// 题目：给定一个数字，我们按照如下规则把它翻译为字符串：0翻译成"a"，1翻
// 译成"b"，……，11翻译成"l"，……，25翻译成"z"。一个数字可能有多个翻译。例
// 如12258有5种不同的翻译，它们分别是"bccfi"、"bwfi"、"bczi"、"mcfi"和
// "mzi"。请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

// 思路：设f(i)表示从第i位数字开始的不同翻译数目，则
// f(i)=f(i+1)+g(i,i+1)*f(i+2)
// 其中，g(i,i+1)=1,当第i位和第i+1位拼接成的数字在10到25之间
//		g(i,i+1)=0,其他

// 这是递归思想（自上而下），但是存在重复计算，
//            f(0)
//           /    \
//		 f(1)     f(2)
//      /   \     /  \
//   f(2)  f(3) f(3) f(4)
// 改成自下而上（这是动态规划的思想）
// 即从最后1位开始，往左求翻译种数。

// @Athor zzg
int GetTranslationCount(int n) {
	if(n<0) return 0;

	string str;
	stringstream ss;
	ss << n;
	ss >> str; //可以用std::to_string();
	//if (str.empty() || str[0] == '-' || str[0] == '+') return 0;

	int sz = str.size();
	if (sz == 1) return 1;

	int res = 0;

	int pos = sz - 2;
	int first = 1, second = 1, factor = 0;
	while (pos >= 0) {
		char ch[3] = { str[pos],str[pos + 1],'\0' };
		if (strcmp(ch, "10") >= 0 && strcmp(ch, "25") <= 0)
			factor = 1;
		else
			factor = 0;
		
		res = first + factor * second;
		second = first;
		first = res;

		pos--;
	}

	return res;
}



// 《剑指offer》
// 辅助内存
int GetTranslationCount(int n){
	if(n<0) return 0;
	string numberInString = to_string(n);

	return GetTranslationCount(numberInString);
}

// f(i)=f(i+1)+g(i,i+1)*f(i+2)
int GetTranslationCount(const string& number){
	int length=number.length();
	int *counts=new int[length];
	int count=0;

	for(int i=length-1;i>=0;--i){
		count=0;
		if(i<length-1)
			count=counts[i+1]; //取出上一步的结果f(i+1)
		else
			count=1;

		if(i<length-1){
			int digit1=number[i]-'0';
			int digit2=number[i+1]-'0';
			int converted=digit1*10+digit2;
			if(converted>=10 && converted<=25){
				if(i<length-2)
					count+=counts[i+2]; //取出上两步的结果f(i+2)
				else
					count+=1; //倒数两个数可组成的翻译数 count=2=1+1
			}
		}

		counts[i]=count; //存储本次结果
	}

	count=counts[0];
	delete[] counts;

	return count;
}