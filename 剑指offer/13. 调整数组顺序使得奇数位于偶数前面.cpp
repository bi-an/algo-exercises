class Solution {
public:
	void reOrderArray(vector<int> &array) {
		vector<int> odd, even;
		for (auto iter = array.begin(); iter != array.end(); iter++) {
			int item = *iter;
			if (item & 1 == 0) {
				even.push_back(item);
			}
			else {
				odd.push_back(item);
			}
		}
		for (size_t i = 0; i < odd.size();i++) {
			array[i] = odd[i];
		}
		for (size_t i = 0; i < even.size(); i++) {
			array[i + odd.size()] = even[i];
		}
	}
};


//两个指针，p1从头开始，p2从尾开始。
//不满足要求，这样奇奇之间、偶偶之间顺序会变化。
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		int pre = 0, post = array.size() - 1;
		while (pre < post) {
			if (isEven(array[pre])) {
				if (!isEven(array[post])) {
					swap(array[pre], array[post]);
					pre++;
					post--;
					continue;
				}
			}
			else
				pre++;
		}
	}
	bool isEven(int num) {
		return (num & 1) == 0; //& 优先级低于 == 
	}
};

//发散思维，输入函数指针，这样可以改变isEven这样的判断函数
void reOrderArray(vector<int> &array, bool (*pf) (int)) {
	int pre = 0, post = array.size() - 1;
	while (pre < post) {
		if (isEven(array[pre])) {
			if (!isEven(array[post])) {
				swap(array[pre], array[post]);
				pre++;
				post--;
				continue;
			}
		}
		else
			pre++;
	}
}


//冒泡法
//时间复杂度：O(n^2)
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		for (int i = 0; i < array.size(); i++) {
			for (int j = array.size() - 1; j > i; j--) {
				if (array[j] % 2 == 1 && array[j - 1] % 2 == 0)
					swap(array[j], array[j - 1]);
			}
		}
	}
};


//STL的stable_partition(iterator1, iterator2, comp)函数
//函数功能是将数组中　comp为真的放在数组前，假的放在数组后，和题意相符
class Solution {
public:
	void reOrderArray(vector<int> &array) {
		stable_partition(array.begin(), array.end(), comp);
	}
	static bool comp(int num) { //这里必须时静态成员函数或者全局函数
		return (num & 1) == 1; //& 优先级低于 == 
	}
};
