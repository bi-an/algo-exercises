// 面试题59（一）：滑动窗口的最大值
// 题目：给定一个数组和滑动窗口的大小，请找出所有滑动窗口里的最大值。例如，
// 如果输入数组{2, 3, 4, 2, 6, 2, 5, 1}及滑动窗口的大小3，那么一共存在6个
// 滑动窗口，它们的最大值分别为{4, 4, 6, 6, 6, 5}，

class Solution {
public:
	vector<int> maxInWindows(const vector<int>& num, unsigned int size)
	{
		vector<int> res;
		if (num.empty() || size <= 0 || size > num.size()) return res;

		deque<int> index; //存储下标，用来判断是否在滑动窗口内
		for (int i = 0; i < size; i++) {
			while (!index.empty() && num[index.back()] < num[i]) // 如果队列中已有数字小于待存入数字，那么这些数字不可能是最大值，删掉它；否则留下它
				index.pop_back(); //保持双端队列头为当前最大值
			index.push_back(i);
		}
		res.push_back(num[index.front()]);
		for (int i = size; i < num.size(); i++) {
			while (!index.empty() && num[index.back()] < num[i])
				index.pop_back();

			index.push_back(i);

			if (i - index.front() >= size) //如果队列头不在窗口内，则删掉头
				index.pop_front();

			res.push_back(num[index.front()]);
		}
		return res;
	}
};