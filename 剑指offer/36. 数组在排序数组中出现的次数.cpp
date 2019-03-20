class Solution {
public:
	int GetNumberOfK(vector<int> data, int k) {
		if (data.empty()) return 0;
		int first = GetFirstK(data,k);
		int last = GetLastK(data,k);
		if (first != -1)
			return last - first + 1;
		else
			return 0;
	}

	//TODO: 可以先判断left和right部分是否等于k，若等于，则不需要再去二分查找了
	//若有顺序查找，时间复杂度为O(n)
	//一直使用二分法，时间复杂度为O(log2(n))
	int GetFirstK(vector<int> data,int k) {
		int left = 0, right = data.size() - 1;
		int mid = 0;
		while (right - left > 1) {
			mid = left + (right - left) / 2;
			if (data[mid] == k) {
				if (data[mid - 1] == k) {
					right = mid - 1;//避免顺序查找
				}
				else
					return mid;
			}
			else if (data[mid] > k) {
				right = mid;
			}
			else {
				left = mid;
			}
		}
		if (data[left] == k)
			return left;
		else if (data[right] == k)
			return right;
		else
			return -1;
	}

	int GetLastK(vector<int> data, int k) {
		int left = 0, right = data.size() - 1, mid = 0;
		while (right - left > 1) {
			mid = left + (right - left) / 2;
			if (data[mid] == k) {
				if (data[mid+1]==k) {
					left = mid + 1;
				}
				else {
					return mid;
				}
			}
			else if (data[mid] > k) {
				right = mid;
			}
			else {
				left = mid;
			}
		}
		if (data[right] == k)
			return right;
		else if (data[left] == k)
			return left;
		else
			return -1;
	}
};
