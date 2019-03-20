/*一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。请写程序找出这两个只出现一次的数字。*/
class Solution {
public:
	void FindNumsAppearOnce(vector<int> data, int* num1, int *num2) {
		if (!num1 || !num2 || data.empty()) return;
		int tmp = data[0];
		for (size_t i = 1; i < data.size(); i++) {
			tmp = tmp ^ data[i];//异或的结果=这两个不同数字的异或。因为相同数字异或结果为0
		}
		//找出第一个非0比特位
		int f_bit = (tmp ^ (tmp - 1))&tmp;
		vector<int> left, right;
		for (size_t i = 0; i < data.size(); i++) {
			if ((f_bit & data[i]) == 0)
				left.push_back(data[i]);
			else
				right.push_back(data[i]);
		}
		if (!left.empty()) {
			tmp = left[0];
			for (size_t i = 1; i < left.size(); i++) {
				tmp ^= left[i];
			}
			*num1 = tmp;//第一个数
		}
		if (!right.empty()) {
			tmp = right[0];
			for (size_t i = 1; i < right.size(); i++) {
				tmp ^= right[i];
			}
			*num2=tmp;//第二个数
		}
	}
};