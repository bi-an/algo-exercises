
// 面试题47：礼物的最大价值
// 题目：在一个m×n的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值
// （价值大于0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或
// 者向下移动一格直到到达棋盘的右下角。给定一个棋盘及其上面的礼物，请计
// 算你最多能拿到多少价值的礼物？


// mxn辅助内存
// 不能把二维数组名转化为二级指针传入函数，必须为int values[][4]
// 二级指针是先存放一级指针值，再去找到一级指针找到一维数组
// 猜测二维数组是直接计算偏移量求出地址，不然要多出很多内存来存放二级指针
// 所以values为一级指针，调用时把二维数组名强制转化为一级指针

// @Athor zzg
// 错误解法，没有列出所有结果
// 必须由left和up推导出当前的maxValue, 不可从当前maxValue推导right和down的maxValue
int getMaxValue(const int *values, int rows, int cols) {
	if (values == nullptr || rows <= 0 || cols <= 0) return 0;

	int **cache = new int*[rows]; //第(i,j)个元素表示到达(i,j)能拿到的礼物价值总和
	for (int i = 0; i < rows; i++)
		cache[i] = new int[cols];

	int i = 0, j = 0;
	cache[0][0] = values[0];
	while (i < rows - 1 || j < cols - 1) {
		// 以下是错误解法，没有列出所有结果
		// 决定下一步怎么走
		int sumDown=0, sumRight=0;
		if(i<rows-1)
			sumDown = cache[i][j] + values[(i + 1)*cols+j];
		if(j<cols-1)
			sumRight = cache[i][j] + values[i*cols+(j + 1)];

		if (sumRight > sumDown) {
			j++;
			cache[i][j] = sumRight;
		}
		else{
			i++;
			cache[i][j] = sumDown;
		}
	}

	int maxValue=cache[i][j];
	for (int ii = 0; ii < rows; ii++) {
		delete[] cache[ii];
	}
	delete[] cache;

	return maxValue;
}


// mxn辅助内存
// 《剑指offer》
int getMaxValue_solution1(const int* values, int rows, int cols){
	if(values==nullptr || rows<=0 || cols<=0) return 0;

	int **maxValues=new int*[rows];
	for(int i=0;i<rows;i++)
		maxValues[i]=new int[cols];

	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int left=0, up=0;
			if(i>0)
				left=maxValues[i-1][j];
			if(j>0)
				up=maxValues[i][j-1];
			maxValues[i][j]=std::max(left,up) + values[i*cols+j];
		}
	}

	int maxValue=maxValues[rows-1][cols-1];
	for(int i=0;i<rows;i++)
		delete[] maxValues[i];
	delete[] maxValues;

	return maxValue;
}


// (i,j)处的maxValue只取决于(i-1,j)和(i,j-1)，(i-2)以及更高的行的maxValue没有必要保存
// n或者m辅助内存
// 用n辅助内存。
//
// 设f(i,j)为到达(i,j)的最大价值，
// 数组中前j个数字分别是f(i,0),f(i,1),...,f(i,j-1)
// 数组中从第j个数字到最后一个数字分别是f(i-1,j),f(i-1,j+1),...,f(i-1,n-1)
//
//											第j列
//        ------------------------------------------------------------------------
//											f(i-1,j)	f(i-1,j+1)	...	f(i-1,n-1)
//        ------------------------------------------------------------------------
// 第i行	f(i,0)	f(i,1)	...	f(i,j-1)	f(i,j)
//        ------------------------------------------------------------------------
//
//        ------------------------------------------------------------------------
//
// 当(i,j)向右或者向下移动时，始终有f(i,j)左边的f(i,j-1)和上边的f(i-1,j)被保存下来。
// 同理，若保存f(0,j-1),...,f(i,j-1)和f(i-1,j),f(i-1,j+1),...,f(i-1,n-1),则需要max(n,m)的辅助内存。
int getMaxValue_solution2(const int *values, int rows, int cols){
	if(values==nullptr || rows<=0 || cols<=0) return 0;
	
	int *maxValues=new int[cols];
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int left=0, up=0;
			if(j>0)
				left=maxValues[j-1];
			if(i>0)
				up=maxValues[j];
			
			maxValues[j]=(left>up?left:up)+values[i*cols+j]; //三目运算符的优先级非常低
		}
	}
	
	int maxValue=maxValues[cols-1];
	delete[] maxValues;
	return maxValue;
}


// Athor zzg
// 递归 《动态规划的思考艺术》 https://github.com/tianyicui/DP-Book  path.pdf《2.1 矩阵中的寻路》
int getMaxValueCore(const int* values, int rows, int cols, int x, int y, int res);

int getMaxValue_solution3(const int *values, int rows, int cols) {
	if (values == nullptr || rows <= 0 || cols <= 0) return 0;

	int res = getMaxValueCore(values, rows, cols, 0, 0, 0);

	return res;
}

int getMaxValueCore(const int* values, int rows, int cols, int x, int y, int res) {
	if (x > rows - 1 || y > cols - 1) return 0;

	//int res = 0;
	res += values[x*cols + y] + std::max(getMaxValueCore(values, rows, cols, x + 1, y, res), getMaxValueCore(values, rows, cols, x, y + 1, res));

	return res;
}