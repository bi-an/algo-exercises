#pragma once
#include <vector>

// 简单插入排序
// 时间复杂度O(n^2)
// 执行最多次数分别为：2+3+...+n=O(n^2)
// 逆序偶的个数就是交换次数O(I)，其他操作（比较）次数为O(N)，总时间复杂度为O(I+N)，如果逆序偶数为O(N)（例如最后一个数是最小的），那么总复杂度为O(2N)=O(N)
// 最坏情形：完全逆序，逆序偶的个数为C(n,2)=n(n-1)/2，复杂度为O(n^2)，比较和交换次数都是O(N^2)
// 最好情形：完全有序，逆序偶的个数为0，总复杂度为O(N)，交换次数O(1)，比较次数O(N)
// 稳定排序
template<typename T>
void insertSort(std::vector<T>& a) {
	for (int i = 1; i < a.size(); i++) {
		int j;
		int temp = a[i];
		for (j = i; j > 0 && temp < a[j - 1]; j--) { // 比较
			a[j] = a[j - 1]; // 交换
		}
		a[j] = temp;
	}
}


