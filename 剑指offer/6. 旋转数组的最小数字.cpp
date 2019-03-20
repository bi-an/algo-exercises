//本算法错误：当数组没有旋转时，输出错误。（但是能通过牛客网测试，应该是bug）
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.empty()) return -1;

		int left=0, right=rotateArray.size()-1;
		int mid = (left+right) / 2;
		int min = rotateArray[0];

		//if (rotateArray[left] < rotateArray[right]) return 0;//此时没有旋转，最小数字即为第一个数

		while (right-left>1) {
			mid = (left + right) / 2;
			if (rotateArray[left] < rotateArray[mid]) {
				left = mid;//与二分查找不同，这个middle必须重复计入
			}
			else if (rotateArray[mid] < rotateArray[right]) {
				right = mid;//与二分查找不同，这个middle必须重复计入
			}
			else {
				for (size_t i = left; i <= right;i++) {
					if (min > rotateArray[i])
						min = rotateArray[i];
				}
				return min;
			}
		}
		min = rotateArray[left] > rotateArray[right] ? rotateArray[right] : rotateArray[left];
		return min;
	}
};


//自己写的。
//发现规律：左边第一个数一定大于等于最右边的数
class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		if (rotateArray.empty()) return 0;
		int left = 0, right = rotateArray.size() - 1;
		//if (right == 0) return rotateArray[0];
		//当左右相等时，如：1,0,1,1,1和1,1,1,0,1，是没法判断下一步min属于哪个区间，应该顺序寻找。
		if (rotateArray[left] == rotateArray[right]) {
			while (left < right) {
				if (rotateArray[right] < rotateArray[right - 1])
					return rotateArray[right];
				right--;
			}
			return rotateArray[0];
		}
		//二分法
		int middle = 0;
		while (rotateArray[left] >= rotateArray[right]){//比while (left < right)效率高一些
			if (right - left == 1)
				return rotateArray[left] > rotateArray[right] ? rotateArray[right] : rotateArray[left];
			else {
				middle = (left + right) / 2;
				if (rotateArray[middle] <= rotateArray[right])
					right = middle;
				else if (rotateArray[middle] >= rotateArray[left])
					left = middle;
				//其他情况不存在，所以不需要写else，实际上，上面可以写成if...else...
			}
		}
		return rotateArray[middle];
	}
};