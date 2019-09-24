// 发现规律：每圈打印的第一个数（即左上角第一个数，总是在对角线上）

class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		int row = matrix.size();
		int col = matrix[0].size();

		vector<int> result;
		if (row == 0 || col == 0) return result;
		int left = 0, right = col - 1, top = 0, bottom = row - 1;
		while (left <= right && top <= bottom) {
			//从左到右
			for (int i = left; i <= right; i++) {
				result.push_back(matrix[top][i]);
			}
			//从上到下
			for (int i = top + 1; i <= bottom; i++) {
				result.push_back(matrix[i][right]);
			}
			//从右到左
			if (top != bottom) // 从右到左的下标检测在循环条件中，所以只需要检测上下下标即可
				for (int i = right - 1; i >= left; i--)
					result.push_back(matrix[bottom][i]);
			//从下往上
			if (left != right) // 上下的下标检测在循环条件中，所以只需要检测左右下标
				for (int i = bottom-1; i > top; i--)
					result.push_back(matrix[i][top]);
				
			left++; right--; top++; bottom--;
		}
		return result;
	}
};


// @Athor zzg
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> ans;
        if (matrix.empty() || matrix[0].empty()) return ans;
        int left = 0, right = (int)matrix[0].size() - 1, bottom = (int)matrix.size() - 1;
        while (left <= right && left <= bottom) {
            for (int i = left; i <= right; i++) // 从左到右
                ans.push_back(matrix[left][i]);
            for (int i = left + 1; i <= bottom; i++) // 从上到下
                ans.push_back(matrix[i][right]);
            for (int i = right - 1; i >= left && left!=bottom; i--) // 从右到左：要保证与“从左到右”不是同一行
                ans.push_back(matrix[bottom][i]);
            for (int i = bottom - 1; i >= left + 1 && left!=right; i--) // 从下到上：要保证与“从上到下”不是同一列
                ans.push_back(matrix[i][left]);
            left++, right--, bottom--;
        }
        return ans;
    }
};


// @Athor zzg
// 写法2
class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		vector<int> res;
		if (matrix.size() == 0 || matrix[0].size() == 0) return res;
		int rows = matrix.size(), cols = matrix[0].size();
		int right = cols - 1, bottom = rows - 1;
		for (int i = 0; i <= right && i<=bottom; i++) {
			printACircle(matrix, i, right, bottom, res);
			right--;
			bottom--;
		}
		return res;
	}

	void printACircle(const vector<vector<int>> &matrix, int leftTop, int right, int bottom, vector<int> &res) {
		int rows = matrix.size();
		int cols = matrix[0].size();

		if (leftTop <= right) {
			for (int i = leftTop; i <= right; i++)
				res.push_back(matrix[leftTop][i]);

			if (leftTop < bottom) {
				for (int i = leftTop + 1; i <= bottom; i++) {
					res.push_back(matrix[i][right]);
				}

				if (leftTop < right) {
					for (int i = right - 1; i >= leftTop; i--) {
						res.push_back(matrix[bottom][i]);
					}

					if (bottom - leftTop >= 2) {
						for (int i = bottom - 1; i >= leftTop + 1; i--) {
							res.push_back(matrix[i][leftTop]);
						}
					}
				}
			}
		}
	}
};



// 《剑指offer》
// 发现规律：
// (1)左上角的坐标(x,y)总是x=y;
// (2)最后一圈的左上角：如果为5*5矩阵，最后一圈的左上角为(2,2)，发现5>(2*2);
// 如果为6*6矩阵，最后一圈的左上角为(2,2)，发现5>(2*2);
// 对于长方形矩阵，结论相同，即循环条件是 cols>startX*2 && rows>startY*2.
// 因为每圈遍历之后，剩余的方块长减少2，宽减少2. 短边遍历完之后，整个矩阵就遍历完了。
class Solution {
public:
	vector<int> printMatrix(vector<vector<int> > matrix) {
		vector<int> res;
		int rows = matrix.size();
		if (rows == 0) return res;
		int cols = (matrix[0]).size();
		if (cols == 0) return res;

		int size = rows < cols ? rows : cols;
		for (int i = 0; i*2 < size; i++) {
			printMatrixIncircle(matrix, i, res);
		}
		return res;
	}

	void printMatrixIncircle(vector<vector<int>>& matrix, int start, vector<int>& res) { // startX=startY=start
		int rows = matrix.size();
		int cols = matrix[0].size();

		int endX = cols - 1 - start;
		int endY = rows - 1 - start;

		//if (endX < start || endY < start)
		//	return;

		//从左上至右上打印
		for (int i = start; i <= endX; i++) {
			res.push_back(matrix[start][i]);
		}

		//从右上到右下打印
		if (endY > start) {
			for (int i = start + 1; i <= endY; i++) {
				res.push_back(matrix[i][endX]);
			}
		}

		//从右下到左下打印
		if (endY > start && endX>start) {
			for (int i = endX - 1; i >= start; i--) {
				res.push_back(matrix[endY][i]);
			}
		}

		//从左下到左上打印
		if (endY - start >= 2 && endX-start>=1) {
			for (int i = endY - 1; i > start; i--) {
				res.push_back(matrix[i][start]);
			}
		}
	}
};


// 写法二
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix) {
    	vector<int> res;
    	if(matrix.empty() || matrix[0].empty()) return res;

    	int rows=matrix.size();
    	int cols=matrix[0].size();

    	int start=0;
    	while(cols>start*2 && rows>start*2){
    		printCircle(matrix, start, rows, cols, res);
    		start++;
    	}
    	return res;
    }

    void printCircle(vector<vector<int>> &matrix, int start, int rows, int cols, vector<int> &res){
    	//int rows=matrix.size();
    	//int cols=matrix[0].size();

    	int endX=cols-1-start; //左右对称：1、左右坐标的中位数在中间；2、左上角到矩阵最左边的距离=右上角到矩阵最右边的距离，前提是endX必须大于start
    	int endY=rows-1-start;

    	//从左上到右上打印
    	for(int i=start;i<=endX;i++){
    		res.push_back(matrix[start][i]);
    	}

    	//从右上到右下打印
    	if(endY>start){
    		for(int i=start+1;i<=endY;i++){
    			res.push_back(matrix[i][endX]);
    		}
    	}

    	//从右下到左下打印
    	if(endX>start && endY>start){
    		for(int i=endX-1;i>=start;i--){
    			res.push_back(matrix[endY][i]);
    		}
    	}

    	//从左下到左上打印
    	if(endY-start>1 && endX>start){
    		for(int i=endY-1;i>start;i--){
    			res.push_back(matrix[i][start]);
    		}
    	}
    }
};