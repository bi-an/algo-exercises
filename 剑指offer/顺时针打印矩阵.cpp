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