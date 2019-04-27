// 下标从0开始
// 顶端下沉，将半堆调整成最大堆
// 时间复杂度: O(h)=O(logn)
void reheap(int heap[], int rootIndex, int lastIndex) {
	bool done = false;
	int orphan = heap[rootIndex]; // 暂存堆顶，以后会反复用来比较并下移(实际上是孩子上移)，这样可以避免交换
	int leftChildIndex = rootIndex * 2 + 1;
	while (!done && leftChildIndex <= lastIndex) { // 堆是完全二叉树,没有左子结点就一定没有右子节点;如果既没有左孩子又没有右孩子，说明到达叶子，退出
		int largerChildIndex = leftChildIndex;
		int rightChildIndex = leftChildIndex + 1;
		if (rightChildIndex <= lastIndex && heap[rightChildIndex] > heap[largerChildIndex])
			largerChildIndex = rightChildIndex;
		if (orphan < heap[largerChildIndex]) {
			heap[rootIndex] = heap[largerChildIndex];
			rootIndex = largerChildIndex;
			leftChildIndex = 2 * rootIndex + 1;
		}
		else
			done = true;
	}
	heap[rootIndex] = orphan; // 将orphan放入最后一个叶子
}

// 思路：不断从最大堆中删除堆顶，并且反序放入一个数组中，这个数组就是有序的
// 该算法不需要辅助内存
void heapSort(int numbers[], int n) {
	if (numbers == nullptr || n <= 0) return;
	// 建立初始堆
	for (int rootIndex = n / 2 - 1; rootIndex >= 0; rootIndex--) // 最后一层不需要考虑(只有一个节点的子树不需要调整)
		reheap(numbers, rootIndex, n - 1); // 从子树到父节点的顺序调整，当父节点调整时，子树已经完成调整
	std::swap(numbers[0], numbers[n - 1]);
	for (int lastIndex = n - 2; lastIndex > 0; lastIndex--) {
		reheap(numbers, 0, lastIndex); // 堆顶(树根)下标总是0
		std::swap(numbers[0], numbers[lastIndex]);
	}
}