// 面试题12：矩阵中的路径
// 题目：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有
// 字符的路径。路径可以从矩阵中任意一格开始，每一步可以在矩阵中向左、右、
// 上、下移动一格。如果一条路径经过了矩阵的某一格，那么该路径不能再次进入
// 该格子。例如在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字
// 母用下划线标出）。但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个
// 字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。
// A B T G
// C F C S
// J D E H

class Solution {
public:
	bool hasPath(char* matrix, int rows, int cols, char* str)
	{
		if (matrix == nullptr || rows <= 0 || cols <= 0 || str == nullptr)
			return false;

		bool *visited = new bool[rows*cols]();
		int pathPos = 0;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				if (hasPathCore(matrix, rows, cols, i, j, str, visited, pathPos)) {//任意选一个格子，该格子中的元素在路径中
					delete[] visited;
					return true;
				}
			}
		}

		delete[] visited;
		return false;
	}
	bool hasPathCore(const char* matrix, int rows, int cols, int row, int col, char* str, bool *visited, int& pathPos) {
		if (str[pathPos] == '\0') 
			return true;

		int hasPath = false;
		if (row >= 0 && row < rows && col >= 0 && col < cols && !visited[row*cols+col] && matrix[row*cols + col] == str[pathPos]) {
			visited[row*cols + col] = true;
			++pathPos;
			hasPath = hasPathCore(matrix, rows, cols, row - 1, col, str, visited, pathPos)
				|| hasPathCore(matrix, rows, cols, row, col - 1, str, visited, pathPos)
				|| hasPathCore(matrix, rows, cols, row + 1, col, str, visited, pathPos)
				|| hasPathCore(matrix, rows, cols, row, col + 1, str, visited, pathPos);
			
			if (!hasPath) {
				visited[row*cols + col] = false;
				--pathPos;
			}
		}
		return hasPath;
	}
};